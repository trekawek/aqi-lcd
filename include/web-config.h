#ifndef _WEB_CONFIG_H
#define _WEB_CONFIG_H

#include <Arduino.h>
#include <DoubleResetDetector.h>
#include <ESP8266WiFi.h>
#include <IotWebConf.h>

#include "config.h"
#include "frontend.h"
#include "model.h"

#define CONFIG_VERSION "aqiled1"
#define DRD_TIMEOUT 10
#define DRD_ADDRESS 0

class WebConfig {
  public:
  WebConfig(Frontend *frontend, std::function<void(Config)> wifiConnected);
  void update();

  private:
  Frontend *frontend;

  char sensorUrl[512];
  char sensorType[16];
  char timezoneOffset[5];
  char sensorAltitude[5];

  DoubleResetDetector *drd;

  DNSServer *dnsServer;
  WebServer *server;
  IotWebConf *iotWebConf;

  IotWebConfParameter *sensorUrlParam;
  static const String SENSOR_TYPE_NAMES[];
  static const String SENSOR_TYPE_VALUES[];
  IotWebConfParameter *sensorTypeParam;
  IotWebConfParameter *timezoneOffsetParam;
  IotWebConfParameter *sensorAltitudeParam;
  boolean displayLogs = true;

  boolean formValidator();
  boolean connectAp(const char* apName, const char* password);
  void connectWifi(const char* ssid, const char* password);
  void handleRoot();
  void setConfig(Config *config);
  void displayConfig();
};

#endif