/*
  В този пример се изпращат команди за промяна силата на звука към телевизор LG (протокол NEC),
  като се използват двата бутона (SW1 и SW2) и инфрачервения светодиод (IR_TX).

  Двата бутона (SW1 и SW2) са свързани съответно към пинове D19 и D18.
  Инфрачервеният светодиод е свързан към пин D17.

  Използва се допълнителната библиотека "IRremoteESP8266" на "crankyoldgit",
  която трябва да се инсталира предварително (https://github.com/crankyoldgit/IRremoteESP8266)
*/

// включване на допълнителната библиотека за работа с инфрачервен светодиод
#include <IRremoteESP8266.h>
#include <IRsend.h>

// константи, описващи използваните пинове
const int SW1_pin = 19;
const int SW2_pin = 18;
const int IR_TX_pin = 17;

// глобални променливи
int SW1_state;
int SW2_state;
IRsend irsend(IR_TX_pin);

void setup() {
   // настройване на пиновете на бутоните като "входове"
  pinMode(SW1_pin, INPUT_PULLUP);
  pinMode(SW2_pin, INPUT_PULLUP);

  // настройване на библиотеката за работа с инфрачервен светодиод
  irsend.begin();
}

void loop() {
  // прочитане на състояниета на бутоните (0/LOW при натиснат, 1/HIGH при отпуснат):
  SW1_state = digitalRead(SW1_pin);
  SW2_state = digitalRead(SW2_pin);

  // проверка за натиснати бутони:
  if (SW1_state == LOW) {
    // намаляване на звука:
    irsend.sendNEC(0x20DFC03F);
  }

  if (SW2_state == LOW) {
    // увеличаване на звука:
    irsend.sendNEC(0x20DF40BF);
  }

  delay(100);
}
