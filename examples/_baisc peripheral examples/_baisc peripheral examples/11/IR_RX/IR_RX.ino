/*
  В този пример се демонстрира прочитането на кодовете на сигнали от дистанционни управления с
  помощта на инфрачервения приемник (IR_RX).
  Прочетените кодове се показват на серийния монитор (Tools -> Serial Monitor)

  Инфрачервеният приемник е свързан към пин D16.

  Използва се допълнителната библиотека "IRremoteESP8266" на "crankyoldgit",
  която трябва да се инсталира предварително (https://github.com/crankyoldgit/IRremoteESP8266)
*/

// включване на допълнителната библиотека за работа с инфрачервен приемник
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// константи, описващи използваните пинове
const int IR_RX_pin = 16;

// глобални променливи
decode_results results;
IRrecv irrecv(IR_RX_pin);

void setup() {
  // настройване на библиотеката за работа с инфрачервен приемник
  irrecv.enableIRIn();

  // настройване на серийната комуникация
  // Забележка: в серийният монитор трябва да бъде избрана същата скорост
  Serial.begin(115200);
}

void loop() {
  // прочитане на сигнала и показване на кода
  if (irrecv.decode(&results)) {
    serialPrintUint64(results.value, HEX);
    Serial.println("");
    irrecv.resume();
  }
  delay(100);
}
