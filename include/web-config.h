#ifndef _WEB_CONFIG_H
#define _WEB_CONFIG_H

#include <Arduino.h>

#include "model.h"

typedef struct {
  String sensorUrl;
  SensorType sensorType;
  int timeZoneOffset;
} Config;

void initWebConfig(std::function<void(Config)> wifiConnected, Adafruit_ILI9341 *tft);

void webConfigLoop();

#endif