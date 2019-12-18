#ifndef _WEB_CONFIG_H
#define _WEB_CONFIG_H

#include <Arduino.h>
#include <DoubleResetDetector.h>
#include <ESP8266WiFi.h>
#include <IotWebConf.h>

#include "config.h"
#include "frontend.h"
#include "model.h"

#define CONFIG_VERSION "aq01"
#define DRD_TIMEOUT 10
#define DRD_ADDRESS 0

class WebConfig {
  public:
  WebConfig(Logger *logger, CustomWebConfig *customWebConfig, std::function<void(Config)> wifiConnected);
  void update();

  private:
  Logger *logger;
  CustomWebConfig *customWebConfig;

  char sensorUrl[512];
  char sensorType[16];

  DoubleResetDetector *drd;

  DNSServer *dnsServer;
  WebServer *server;
  IotWebConf *iotWebConf;

  IotWebConfParameter *sensorUrlParam;
  static const String SENSOR_TYPE_NAMES[];
  static const String SENSOR_TYPE_VALUES[];
  IotWebConfParameter *sensorTypeParam;
  boolean displayLogs = true;

  boolean formValidator();
  boolean connectAp(const char* apName, const char* password);
  void connectWifi(const char* ssid, const char* password);
  const int32_t calcWiFiSignalQuality(int32_t rssi);
  void handleRoot();
  void setConfig(Config *config);
  void displayConfig();
};

#endif