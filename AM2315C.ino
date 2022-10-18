#include <Adafruit_AHTX0.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>
#include <Wire.h>

//ESP32-WROOM
oPop
#define TFT_DC 12 //A0
#define TFT_CS 13 //CS
#define TFT_MOSI 14 //SDA
#define TFT_CLK 27 //SCK
#define TFT_RST 0
#define TFT_MISO 0
// REST 3.3v

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);

Adafruit_AHTX0 aht;
sensors_event_t humidity, temp;
void setup() {
  Serial.begin(115200);
  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println();
  Serial.println("Temperature C || Humidity %rH");
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(2);
}
void loop() {
  aht.getEvent(&humidity, &temp);
  Serial.print(temp.temperature);
  Serial.print("                ");
  Serial.println(humidity.relative_humidity);
  Serial.println(temp.temperature);
  Serial.println(humidity.relative_humidity);

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextWrap(false);
  tft.setCursor(0, 60);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print("Temp:");
  tft.print(temp.temperature);
  tft.setCursor(0, 80);
  //  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print("Hum:");
  tft.print(humidity.relative_humidity);
  tft.setCursor(0, 150);
  //  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.print("By CloudStakes");
  
  delay(1000);
}
