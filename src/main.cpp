#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "data-source.h"
#include "display-clock.h"
#include "fetcher.h"
#include "interface.h"
#include "touch-interface.h"
#include "web-config.h"

boolean connected = false;

TFT_eSPI *tft = new TFT_eSPI();
DisplayClock *displayClock;
Interface *interface;
DataSource *dataSource;
Fetcher *fetcher;
WebConfig *webConfig;
TouchInterface *touchInterface;

void wifiConnected(Config config) {
  tft->fillScreen(0);
  displayClock = new DisplayClock(tft, config.timeZoneOffset);
  dataSource = DataSource::createDataSource(config.sensorType, config.sensorUrl);
  interface = new Interface(tft);
  fetcher = new Fetcher(interface, dataSource);
  touchInterface = new TouchInterface(tft, interface);
  connected = true;
}

void setup() {
  Serial.begin(9600);
  Serial.println("AQI LCD is starting!");
  tft->begin();
  tft->setRotation(0);
  tft->fillScreen(0);
  webConfig = new WebConfig(tft, &wifiConnected);
}

void loop(void) {
  webConfig->update();
  if (connected) {
    fetcher->update();
    displayClock->update();
    touchInterface->update();
  }
}
