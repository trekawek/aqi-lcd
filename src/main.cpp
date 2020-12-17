#include <Arduino.h>

#include "data-source.h"
#include "fetcher.h"
#include "frontend.h"
#include "mdns-resolver.h"
#include "web-config.h"

boolean connected = false;
DataSource *dataSource;
WebConfig *webConfig;
Fetcher *fetcher;
MDNSResolver *mdnsResolver;

#if FRONTEND_LCD
#include "lcd/lcd-frontend.h"
Frontend *frontend = new LcdFrontend();
#elif FRONTEND_LED
#include "led/led-frontend.h"
Frontend *frontend = new LedFrontend();
#else
#error "Either FRONTEND_LCD or FRONTEND_LED should be set"
#endif

void wifiConnected(Config config, IPAddress localIp) {
  if (connected) {
    return;
  }

  dataSource = DataSource::createDataSource(config.sensorType, config.sensorUrl, mdnsResolver);
  fetcher = new Fetcher(frontend, dataSource);
  frontend->connected(config, dataSource);
  connected = true;
}

void setup() {
  Serial.begin(115200);
  Serial.println("AQI LCD is starting!");
  frontend->init();
  mdnsResolver = new MDNSResolver();
  webConfig = new WebConfig(frontend->getLogger(), frontend->getCustomWebConfig(), &wifiConnected);
}

void loop() {
  webConfig->update();
  mdnsResolver->loop();
  if (connected) {
    fetcher->update();
    frontend->doLoop();
  }
}
