#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

#include "clock.h"
#include "model.h"
#include "fetcher.h"
#include "web-config.h"

#define TFT_CS D8
#define TFT_DC D1
#define TS_CS  D2

boolean connected = false;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
XPT2046_Touchscreen ts(TS_CS);

void wifiConnected(Config config) {
  tft.fillScreen(0);
  initClock(config.timeZoneOffset);
  initFetcher(config.sensorUrl, config.sensorType);
  connected = true;
}

void setup() {
  Serial.begin(9600);
  Serial.println("AQI LCD is starting!");

  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(0);

  initWebConfig(&wifiConnected, &tft);
}

void loop(void) {
  webConfigLoop();
  if (connected) {
    updateDisplay(&tft);
    updateClock(&tft);
    TS_Point p = ts.getPoint();
    if (ts.touched()) {
      
    }
  }
}
