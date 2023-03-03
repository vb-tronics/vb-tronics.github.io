/*
  В този пример се изпращат команди за промяна силата на звука към телевизор LG (протокол NEC),
  като се използват двата бутона (SW1 и SW2) и инфрачервения светодиод (IR_TX).

  Двата бутона (SW1 и SW2) са свързани съответно към пинове D19 и D18.
  Инфрачервеният светодиод е свързан към пин D17.

  Използва се функцията "irSendNECblk" на "6v6gt"
  източник: Extreme Lightweight IR Sender for NEC protocol (https://forum.arduino.cc/t/extreme-lightweight-ir-sender-for-nec-protocol/858910)
*/

// константи, описващи използваните пинове
const int SW1_pin = 19;
const int SW2_pin = 18;
const int IR_TX_pin = 17;

// променливи, използвани при четенето на бутонтие
int SW1_state;
int SW2_state;

// функция, управляваща инфрачервения светодиод
    void irSendNECblk( uint32_t code, uint8_t irLedPin, uint8_t freqKhz, bool inverted = false, bool invertedBitOrder = false ) {
      // sends an NEC IR code. No library required. Just copy this function into your sketch.
      // where:
      // code:  the code to send e.g. 0x00FDA857
      // irLedPin: the output pin e.g. 3
      // freqKhz: the carrier frequency in KHz
      // inverted: (default false). Default case : led wired low side so pin HIGH = on. otherwise pin LOW = on.
      // invertedBitOrder (default false). Default case: MSB as used in ver <= 2  of the Ken Shirriff IR library. Otherwise mirrored for V3+
    
      // sample call: irSendNECblk( 0x00FF1A9B, 3, 38 )  // pin 3, 38kHz carrier, pin HIGH puts led on, original (non mirrored) hex code format.
      // Note: blocks the loop() for approx 70 ms .
      // Author: 6v6gt 04.05.2021 https://forum.arduino.cc/t/extreme-lightweight-ir-sender-for-nec-protocol/858910
    
      uint16_t NecBurstUnit = ( freqKhz * 562L) / 1000L ; // IR carrier waves for 1 NEC mark or 1 NEC space( bit 0).
      uint8_t carrierPeriodUs = (int16_t)1000 / freqKhz ;
      uint8_t * codeSplit ;
      codeSplit = ( uint8_t* ) &code ;  // treat uint32_t as byte array ;
    
      auto xmit = [irLedPin,  inverted, carrierPeriodUs ]( bool isOn, uint16_t waves ) {
        // send carrier burst. on = IR mark, otherwise IR space (filler)
        uint32_t burstStartUs = micros() ;
    
        for ( uint16_t i = 0 ; i < waves ; i ++ ) {
          digitalWrite( irLedPin , isOn != inverted ? HIGH : LOW ) ;  // Xor. carrier mark or filler
          delayMicroseconds( carrierPeriodUs / 3 ) ;  // 33% duty cycle
          digitalWrite( irLedPin, inverted ? HIGH : LOW ) ;   // carrier space
          while (  micros() - ( burstStartUs + ( i * carrierPeriodUs ) ) < carrierPeriodUs )  ;  // idle until end of wave(i)
        } ;
      } ;
    
      pinMode( irLedPin, OUTPUT ) ;
      xmit( true , NecBurstUnit * 16 ) ;   // header mark 9000 us
      xmit( false , NecBurstUnit * 8 ) ;   // header space 4500 us
      for ( uint8_t i = 0 ; i < 32 ; i ++ ) {  // 32 bits
        xmit( true , NecBurstUnit ) ; // NEC mark
        uint8_t codeByte = !invertedBitOrder ? 3 - i / 8 /*MSB*/ : i/8 /*LSB*/ ;
        uint8_t codeBit = !invertedBitOrder ? 7 - i % 8 /*MSB*/ : i % 8 /*LSB*/ ;
        xmit( false, bitRead( *(codeSplit + codeByte) , codeBit ) == 1   ? NecBurstUnit * 3 : NecBurstUnit ) ;  // NEC space(0) 562us or NEC space(1) ~1675us
      }
      xmit( true , NecBurstUnit ) ;  // terminator
    } // end of irSendNECblk()



void setup() {
   // настройване на пиновете на бутоните като "входове"
  pinMode(SW1_pin, INPUT_PULLUP);
  pinMode(SW2_pin, INPUT_PULLUP);
}

void loop() {
  // прочитане на състояниета на бутоните (0/LOW при натиснат, 1/HIGH при отпуснат):
  SW1_state = digitalRead(SW1_pin);
  SW2_state = digitalRead(SW2_pin);

  // проверка за натиснати бутони:
  if (SW1_state == LOW) {
    // намаляване на звука:
    irSendNECblk(0x20DFC03F, IR_TX_pin, 38);
  }

  if (SW2_state == LOW) {
    // увеличаване на звука:
    irSendNECblk(0x20DF40BF, IR_TX_pin, 38);
  }

  delay(100);
}
