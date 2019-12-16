#include <Arduino.h>
#include <Wire.h>

#include "data-source.h"
#include "fetcher.h"
#include "frontend.h"
#include "web-config.h"

boolean connected = false;
DataSource *dataSource;
WebConfig *webConfig;
Fetcher *fetcher;

#if FRONTEND_LCD
#include "lcd/lcd-frontend.h"
Frontend *frontend = new LcdFrontend();
#elif FRONTEND_LED
#include "led/led-frontend.h"
Frontend *frontend = new LedFrontend();
#else
#error "Either FRONTEND_LCD or FRONTEND_LED should be set"
#endif

void wifiConnected(Config config) {
  if (connected) {
    return;
  }
  dataSource = DataSource::createDataSource(config.sensorType, config.sensorUrl);
  fetcher = new Fetcher(frontend, dataSource);
  frontend->connected(config, dataSource);
  connected = true;
}

void setup() {
  Serial.begin(115200);
  Serial.println("AQI LCD is starting!");
  pinMode(D3, OUTPUT);
  pinMode(TX, FUNCTION_3);
  pinMode(RX, FUNCTION_3);
  Wire.begin(TX, RX);
  frontend->init();
  webConfig = new WebConfig(frontend, &wifiConnected);
}

void loop(void) {
  webConfig->update();
  if (connected) {
    fetcher->update();
    frontend->doLoop();
  }
}
