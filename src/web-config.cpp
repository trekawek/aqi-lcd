#include "web-config.h"

const String WebConfig::SENSOR_TYPE_NAMES[] = {"aqi.eco", "local device", ""};
const String WebConfig::SENSOR_TYPE_VALUES[] = {"AQI_ECO", "LOCAL_DEVICE", ""};

WebConfig::WebConfig(Frontend *frontend, std::function<void(Config)> wifiConnected) {
  this->frontend = frontend;
  this->frontend->println("Initializing device...");

  this->dnsServer = new DNSServer();
  this->server = new WebServer(80);
  this->iotWebConf = new IotWebConf("AQI LCD", this->dnsServer, this->server, NULL, CONFIG_VERSION);

  this->sensorUrlParam = new IotWebConfParameter("Sensor URL", "sensorUrl", this->sensorUrl, 512);
  this->sensorTypeParam = new IotWebConfParameter("Sensor type", "sensorType", this->sensorType, 16, "select", SENSOR_TYPE_NAMES, SENSOR_TYPE_VALUES, "AQI_ECO");
  this->timezoneOffsetParam = new IotWebConfParameter("Timezone offset (hours)", "timezoneOffset", this->timezoneOffset, 5, "number", NULL, "1", "min=\"-12\" max=\"12\"");
  this->backlightTimeParam = new IotWebConfParameter("Backlight time (seconds)", "backlightTime", this->backlightTime, 5, "number", NULL, "10", "min=\"0\" max=\"60\"");
  this->iotWebConf->addParameter(this->sensorUrlParam);
  this->iotWebConf->addParameter(this->sensorTypeParam);
  this->iotWebConf->addParameter(this->timezoneOffsetParam);
  this->iotWebConf->addParameter(this->backlightTimeParam);
  this->iotWebConf->setFormValidator([this]{ return this->formValidator(); });
  this->iotWebConf->setWifiConnectionCallback([wifiConnected, this]{
    Config config;
    this->setConfig(&config);
    if (this->displayLogs) {
      this->displayConfig();
      this->displayLogs = false;
    }
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

  if (this->server->arg(this->backlightTimeParam->getId()).length() == 0) {
    this->backlightTimeParam->errorMessage = "Please provide backlight time or 0 for disable.";
    valid = false;
  }

  return valid;
}

boolean WebConfig::connectAp(const char* apName, const char* password) {
  if (this->displayLogs) {
    this->frontend->println("Creating access point");
    this->frontend->println("SSID:     " + String(apName));
    this->frontend->println("Password: " + String(password));
  }
  return WiFi.softAP(apName, password);
}

void WebConfig::connectWifi(const char* ssid, const char* password) {
  if (this->displayLogs) {
    this->frontend->print("Connecting to WiFi ");
    this->frontend->println(ssid);
  }
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
  config->backlightTime = String(this->backlightTime).toInt();
}

void WebConfig::displayConfig() {
  this->frontend->print("Local IP:         ");
  this->frontend->println(WiFi.localIP().toString());

  this->frontend->print("Sensor type:      ");
  this->frontend->println(this->sensorType);
  this->frontend->println("Sensor URL:");
  this->frontend->println(this->sensorUrl);
  this->frontend->print("Timezeone offset: ");
  this->frontend->println(this->timezoneOffset);
  this->frontend->print("Backlight time: ");
  this->frontend->println(this->backlightTime);

  delay(1000 * 2);
}
