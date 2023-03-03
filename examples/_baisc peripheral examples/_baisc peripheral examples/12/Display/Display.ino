/*
  В този пример се демонстрира работата с графичен OLED дисплей (128x64 пиксела, едноцветен)
  
  За комуникация с дисплея се използва интерфейс I2C (сигнали SDA и SCL, свързани към пинове D21 и D22)
  Използва се допълнителната библиотека "Universal 8bit Graphics Library" на "olikraus",
  която трябва да се инсталира предварително (https://github.com/olikraus/u8g2/)
*/

// включване на допълнителните библиотеки за работа с дисплея
#include <U8g2lib.h>
#include <Wire.h>

// константи, описващи използваните пинове
const int I2C_SDA_pin = 21;
const int I2C_SCL_pin = 22;

// константи, съдържащи изображенията
const unsigned char happy_30x30[] PROGMEM = {
  0x00, 0xFC, 0x1F, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0xC0, 0xFF, 0xFF, 0x03, 
  0xF0, 0x07, 0xE0, 0x07, 0xF0, 0x01, 0x80, 0x0F, 0x78, 0x00, 0x00, 0x1E, 
  0x3C, 0x00, 0x00, 0x1C, 0x1E, 0x18, 0x30, 0x38, 0x0E, 0x1C, 0x78, 0x38, 
  0x0E, 0x1C, 0x78, 0x30, 0x07, 0x1C, 0x78, 0x30, 0x07, 0x1C, 0x78, 0x30, 
  0x07, 0x1C, 0x38, 0x30, 0x07, 0x00, 0x00, 0x30, 0x07, 0x00, 0x00, 0x32, 
  0x07, 0x00, 0x00, 0x33, 0x87, 0x01, 0x00, 0x33, 0x87, 0x01, 0x80, 0x33, 
  0x87, 0x03, 0xC0, 0x39, 0x87, 0x07, 0xC0, 0x39, 0x06, 0x0F, 0xE0, 0x38, 
  0x0E, 0x3E, 0x78, 0x18, 0x0E, 0xFC, 0x7F, 0x1C, 0x1C, 0xF0, 0x1F, 0x0E, 
  0x38, 0x80, 0x07, 0x0F, 0x78, 0x00, 0x80, 0x07, 0xF0, 0x01, 0xC0, 0x07, 
  0xC0, 0x0F, 0xF8, 0x03, 0x80, 0xFF, 0xFF, 0x00, 0x00, 0xFC, 0x3F, 0x00,
};

const unsigned char like_30x30[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x0F, 0x00, 0x00, 0x80, 0x1F, 0x00, 0x00, 0x80, 0x1F, 0x00, 
  0x00, 0x80, 0x3B, 0x00, 0x00, 0x80, 0x3B, 0x00, 0x00, 0x80, 0x3B, 0x00, 
  0x00, 0x80, 0x39, 0x00, 0x00, 0xC0, 0x39, 0x00, 0x00, 0xE0, 0xF8, 0x3F, 
  0x00, 0xF0, 0xF8, 0x3F, 0xFF, 0x7B, 0x00, 0x30, 0xFF, 0x3F, 0xC0, 0x3F, 
  0x07, 0x1F, 0xC0, 0x3F, 0x07, 0x07, 0x80, 0x3F, 0x07, 0x03, 0x00, 0x30, 
  0x07, 0x03, 0xC0, 0x3F, 0x07, 0x03, 0xC0, 0x3F, 0x07, 0x03, 0x00, 0x30, 
  0x07, 0x03, 0x00, 0x38, 0x07, 0x03, 0xC0, 0x1F, 0x07, 0x03, 0xC0, 0x1F, 
  0x07, 0x0F, 0x00, 0x0C, 0x07, 0x1F, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0x07, 
  0xFF, 0xF3, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// настройване на библиотеката: завъртане, RESET пин, SCL пин, SDA пин
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, I2C_SCL_pin, I2C_SDA_pin);

void setup() {
  // инициализиране на библиотеката
  u8g2.begin();
}

void loop() {
  // начало на изчертаването
  u8g2.firstPage();  
  do {
    u8g2.drawFrame(0,0,u8g2.getDisplayWidth(),u8g2.getDisplayHeight() );

    // текст: задаване на размер на шрифта, цвят, посока и позиция
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
    u8g2.drawStr( 34, 10, "VB-tronics");

    // изображения: задаване на режим, позиция и размери
    // https://www.online-utility.org/image/convert/to/XBM
    u8g2.setBitmapMode(false /* solid */);
    u8g2.drawXBMP(1, 1, 30, 30, happy_30x30);
    u8g2.drawXBMP(97, 1, 30, 30, like_30x30);

    // правоъгълник: задаване на позиция и размери
    u8g2.drawFrame(10,35,10,10);

    // запълнен правоъгълник: задаване на позиция и размери
    u8g2.drawBox(10,50,10,10);

    // окръжност: задаване на център и радиус
    u8g2.drawCircle(45,40,5);

    // запълнена окръжност: задаване на център и радиус
    u8g2.drawDisc(45,55,5);

    // правоъгълник със заоблени ъгли: задаване на позиция, размери и радиус на заобляне
    u8g2.drawRFrame(70,35,20,10,5);

    // запълнен правоъгълник със заоблени ъгли: задаване на позиция, размери и радиус на заобляне
    u8g2.drawRBox(70,50,20,10,5);

    // линии: задаване на начало и край
    u8g2.drawLine(110,35,115,45);
    u8g2.drawLine(115,45,105,45);
    u8g2.drawLine(105,45,110,35);

    // триъгълник: задаване на трите точки
    u8g2.drawTriangle(110,50,115,60,105,60);

  // край на изчертаването
  } while( u8g2.nextPage() );
  

}
