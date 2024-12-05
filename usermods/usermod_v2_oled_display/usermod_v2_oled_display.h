#pragma once

#include "wled.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "pixils.h"

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define I2C_SDA 8           // SDA pin
#define I2C_SCL 9           // SCL pin
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; (01111000 [0x3C] for SSD1306)
#define SSD1306_NO_SPLASH
#define gndPin 7

TwoWire I2COLED = TwoWire(0);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &I2COLED, OLED_RESET);
signed long lastOLEDUpdate = 0;
int i = 0;

class OledDisplayUserMod : public Usermod
{

private:
public:
  // gets called once at boot. Do all initialization that doesn't depend on
  // network here
  void setup()
  {
    // Pull down BIN pin
    pinMode(gndPin, OUTPUT);
    digitalWrite(gndPin, LOW);

    // Initialize OLED display
    Serial.begin(115200);
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    startUpScreen(display);
    lastOLEDUpdate = millis();
  }

  // gets called every time WiFi is (re-)connected. Initialize own network
  // interfaces here
  void connected()
  {
    display.clearDisplay();
    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 0);
    display.println(F("Connected"));
    display.display();
    display.setTextSize(1);
    display.setCursor(10, 30);
    display.println(F(WiFi.localIP().toString().c_str()));
    display.display();
    delay(10000);
  }

  void loop()
  {
    if (millis() - lastOLEDUpdate > 5000)
    {
      lastOLEDUpdate = millis();
      if (i == 0)
      {
        display.clearDisplay();
        display.drawXBitmap((128 - chase_width) / 2, (64 - chase_height) / 2,
                            chase_data, chase_width, chase_height, 1);
        display.display();
        i = 1;
      }
      else if (i == 1)
      {
        display.clearDisplay();
        display.drawXBitmap((128 - merryChristmas_width) / 2, (64 - merryChristmas_height) / 2,
                            merryChristmas_data, merryChristmas_width, merryChristmas_height, 1);
        display.display();
        i = 2;
      }
      else if (i == 2)
      {
        display.clearDisplay();
        display.drawXBitmap((128 - startScreen2_width) / 2, (64 - startScreen2_height) / 2,
                            startScreen2_data, startScreen2_width, startScreen2_height, 1);
        display.display();
        i = 0;
      }
    }
  }
};