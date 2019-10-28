#include "web-config.h"

WebConfig::WebConfig(TFT_eSPI *tft, std::function<void(Config)> wifiConnected) {
  this->tft = tft;
  this->tft->println("Initializing device...");

  this->dnsServer = new DNSServer();
  this->server = new WebServer(80);
  this->iotWebConf = new IotWebConf("AQI LCD", this->dnsServer, this->server, NULL, CONFIG_VERSION);

  this->sensorUrlParam = new IotWebConfParameter("Sensor URL", "sensorUrl", this->sensorUrl, 512);
  this->sensorTypeParam = new IotWebConfParameter("Sensor type", "sensorType", this->sensorType, 16, "text", "AQI_ECO or LOCAL_DEVICE", "AQI_ECO");
  this->timezoneOffsetParam = new IotWebConfParameter("Timezone offset (hours)", "timezoneOffset", this->timezoneOffset, 5, "number", NULL, "1", "min=\"-12\" max=\"12\"");
  this->iotWebConf->addParameter(this->sensorUrlParam);
  this->iotWebConf->addParameter(this->sensorTypeParam);
  this->iotWebConf->addParameter(this->timezoneOffsetParam);
  this->iotWebConf->setFormValidator([this]{ return this->formValidator(); });
  this->iotWebConf->setWifiConnectionCallback([wifiConnected, this]{
    Config config;
    this->setConfig(&config);
    this->displayConfig();
    wifiConnected(config);
  });
  this->iotWebConf->setApConnectionHandler([this](const char* apName, const char* password){ return this->connectAp(apName, password); });
  this->iotWebConf->setWifiConnectionHandler([this](const char* ssid, const char* password){ return this->connectWifi(ssid, password); });

  this->drd = new DoubleResetDetector(DRD_TIMEOUT, DRD_ADDRESS);
  if (!this->drd->detectDoubleReset()) {
    this->iotWebConf->skipApStartup();
  }
  this->iotWebConf->init();

  this->server->on("/", [this]{ this->handleRoot(); });
  this->server->on("/config", [this]{ this->iotWebConf->handleConfig(); });
  this->server->onNotFound([this](){ this->iotWebConf->handleNotFound(); });
}

void WebConfig::update() {
  this->iotWebConf->doLoop();
  this->drd->loop();
}

boolean WebConfig::formValidator() {
  Serial.println("Validating form.");
  boolean valid = true;

  if (this->server->arg(this->sensorUrlParam->getId()).length() == 0) {
    this->sensorUrlParam->errorMessage = "Please provide the sensor URL.";
    valid = false;
  }

  String sensorTypeVal = this->server->arg(this->sensorTypeParam->getId());
  if (sensorTypeVal != "AQI_ECO" && sensorTypeVal != "LOCAL_DEVICE") {
    this->sensorTypeParam->errorMessage = "Please choose AQI_ECO or LOCAL_DEVICE for the sensor type.";
    valid = false;
  }

  if (this->server->arg(this->timezoneOffsetParam->getId()).length() == 0) {
    this->timezoneOffsetParam->errorMessage = "Please provide the timezone offset.";
    valid = false;
  }

  return valid;
}

boolean WebConfig::connectAp(const char* apName, const char* password) {
  this->tft->println("Creating access point");
  this->tft->println("SSID:     " + String(apName));
  this->tft->println("Password: " + String(password));
  return WiFi.softAP(apName, password);
}

void WebConfig::connectWifi(const char* ssid, const char* password) {
  this->tft->print("Connecting to WiFi ");
  this->tft->println(ssid);
  WiFi.begin(ssid, password);
}

void WebConfig::handleRoot() {
  if (this->iotWebConf->handleCaptivePortal()) {
    return;
  }
  String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
  s += "<title>AQI LCD</title></head><body><p>Hello to AQI LCD!</p>";
  s += "<p>Go to <a href='config'>configure page</a> to change settings.</p>";
  s += "</body></html>\n";
  this->server->send(200, "text/html", s);
}

void WebConfig::setConfig(Config *config) {
  config->sensorUrl = String(this->sensorUrl);
  String sensorTypeStr = String(this->sensorType);
  if (sensorTypeStr == "AQI_ECO") {
    config->sensorType = AQI_ECO;
  } else if (sensorTypeStr = "LOCAL_DEVICE") {
    config->sensorType = LOCAL_DEVICE;
  }
  config->timeZoneOffset = String(this->timezoneOffset).toInt();
}

void WebConfig::displayConfig() {
  this->tft->print("Local IP:         ");
  this->tft->println(WiFi.localIP());

  this->tft->print("Sensor type:      ");
  this->tft->println(this->sensorType);
  this->tft->println("Sensor URL:");
  this->tft->println(this->sensorUrl);
  this->tft->print("Timezeone offset: ");
  this->tft->println(this->timezoneOffset);

  delay(1000 * 2);
}
