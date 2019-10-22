#include <IotWebConf.h>

#include "web-config.h"

#define CONFIG_VERSION "aqiled1"

char sensorUrl[512];
char sensorType[16];
char timezoneOffset[4];

DNSServer dnsServer;
WebServer server(80);
IotWebConf iotWebConf("AQI LCD", &dnsServer, &server, NULL, CONFIG_VERSION);
IotWebConfParameter sensorUrlParam = IotWebConfParameter("Sensor URL", "sensorUrl", sensorUrl, 512);
IotWebConfParameter sensorTypeParam = IotWebConfParameter("Sensor type", "sensorType", sensorType, 16, "text", "AQI_ECO or LOCAL_DEVICE", "AQI_ECO");
IotWebConfParameter timezoneOffsetParam = IotWebConfParameter("Timezone offset (hours)", "timezoneOffset", timezoneOffset, 4, "number", NULL, "1", "min='-12' max='12' step='1'");

void handleRoot() {
  if (iotWebConf.handleCaptivePortal()) {
    return;
  }
  String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
  s += "<title>AQI LCD</title></head><body><p>Hello to AQI LCD!</p>";
  s += "<p>Go to <a href='config'>configure page</a> to change settings.</p>";
  s += "</body></html>\n";
  server.send(200, "text/html", s);
}

boolean formValidator() {
  Serial.println("Validating form.");
  boolean valid = true;

  if (server.arg(sensorUrlParam.getId()).length() == 0) {
    sensorUrlParam.errorMessage = "Please provide the sensor URL.";
    valid = false;
  }

  String sensorTypeVal = server.arg(sensorTypeParam.getId());
  if (sensorTypeVal != "AQI_ECO" && sensorTypeVal != "LOCAL_DEVICE") {
    sensorTypeParam.errorMessage = "Please choose AQI_ECO or LOCAL_DEVICE for the sensor type.";
    valid = false;
  }

  if (server.arg(timezoneOffsetParam.getId()).length() == 0) {
    timezoneOffsetParam.errorMessage = "Please provide the timezone offset.";
    valid = false;
  }

  return valid;
}

void setConfig(Config *config) {
  config->sensorUrl = String(sensorUrl);
  String sensorTypeStr = String(sensorType);
  if (sensorTypeStr == "AQI_ECO") {
    config->sensorType = AQI_ECO;
  } else if (sensorTypeStr = "LOCAL_DEVICE") {
    config->sensorType = LOCAL_DEVICE;
  }
  config->timeZoneOffset = String(timezoneOffset).toInt();
}

void initWebConfig(std::function<void(Config)> wifiConnected) {
  iotWebConf.addParameter(&sensorUrlParam);
  iotWebConf.addParameter(&sensorTypeParam);
  iotWebConf.addParameter(&timezoneOffsetParam);
  iotWebConf.setFormValidator(&formValidator);
  iotWebConf.setWifiConnectionCallback([wifiConnected]{
    Config config;
    setConfig(&config);
    wifiConnected(config);
  });
  iotWebConf.init();

  server.on("/", handleRoot);
  server.on("/config", []{ iotWebConf.handleConfig(); });
  server.onNotFound([](){ iotWebConf.handleNotFound(); });
}

void webConfigLoop() {
  iotWebConf.doLoop();
}