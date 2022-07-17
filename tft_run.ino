#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>
#include <Wire.h>
#define si7021Addr 0x40

// These pins will also work for the 1.8" TFT shield

//ESP32-WROOM
#define TFT_DC 12 //A0
#define TFT_CS 13 //CS
#define TFT_MOSI 14 //SDA
#define TFT_CLK 27 //SCK
#define TFT_RST 0
#define TFT_MISO 0
// REST 3.3v

//sda 21 si7021
//scl 22

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);


void setup() {
  Wire.begin();
  Serial.begin(9600);
  Wire.beginTransmission(si7021Addr);
  Wire.endTransmission();
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(2);
}

void loop() {
  unsigned int data[2];
  Wire.beginTransmission(si7021Addr);
  //Send humidity measurement command
  Wire.write(0xF5);
  Wire.endTransmission();
  delay(500);

  // Request 2 bytes of data
  Wire.requestFrom(si7021Addr, 2);
  // Read 2 bytes of data to get humidity
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data
  float humidity  = ((data[0] * 256.0) + data[1]);
  humidity = ((125 * humidity) / 65536.0) - 6;

  Wire.beginTransmission(si7021Addr);
  // Send temperature measurement command
  Wire.write(0xF3);
  Wire.endTransmission();
  delay(500);

  // Request 2 bytes of data
  Wire.requestFrom(si7021Addr, 2);

  // Read 2 bytes of data for temperature
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data
  float temp  = ((data[0] * 256.0) + data[1]);
  float celsTemp = ((175.72 * temp) / 65536.0) - 46.85;
  float fahrTemp = celsTemp * 1.8 + 32;

  // Output data to serial monitor
  Serial.print("Humidity : ");
  Serial.print(humidity);
  Serial.println(" % RH");
  Serial.print("Celsius : ");
  Serial.print(celsTemp);
  Serial.println(" C");
  Serial.print("Fahrenheit : ");
  Serial.print(fahrTemp);
  Serial.println(" F");

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextWrap(false);
  tft.setCursor(0, 60);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print("Temp:");
  tft.print(celsTemp);
  tft.setCursor(0, 80);
  //  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print("Hum:");
  tft.print(humidity);
  tft.setCursor(0, 150);
  //  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.print("By CloudStakes");

  delay(1000);
}
