#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "clock.h"
#include "model.h"
#include "fetcher.h"
#include "web-config.h"

boolean connected = false;

TFT_eSPI tft = TFT_eSPI();

void wifiConnected(Config config) {
  tft.fillScreen(0);
  initClock(config.timeZoneOffset);
  initFetcher(config.sensorUrl, config.sensorType);
  connected = true;
}

void handleTouch(void) {
  uint16_t t_x = 0, t_y = 0, t_z = 0;

  if (tft.getTouch(&t_x, &t_y, 150)) {
    tft.fillRect(0, 0, 58, 50, TFT_RED);
    tft.setTextColor(TFT_YELLOW);
    t_z = tft.getTouchRawZ();
    tft.setTextSize(1);
    tft.setCursor(0, 12);
    tft.print("X:");
    tft.print(t_x);
    tft.setCursor(0, 30);
    tft.print("Y:");
    tft.print(t_y);
    tft.setCursor(0, 48);
    tft.print("Z:");
    tft.print(t_z);
  } else {
    tft.fillRect(0, 0, 58, 50, TFT_BLACK);
  }
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
    handleTouch();
  }
}
