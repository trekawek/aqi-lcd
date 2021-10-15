#ifdef FRONTEND_LED

#include "led/led-web-config.h"

LedWebConfig::LedWebConfig() {
    this->brightnessParam = new IotWebConfParameter("Brightness", "brightness", this->brightness, 5, "number", NULL, "32", "min=\"0\" max=\"255\"");
    this->ledCountParam = new IotWebConfParameter("Led count", "ledCount", this->ledCount, 6, "number", NULL, "60", "min=\"1\" max=\"65535\"");
}

void LedWebConfig::addParameters(IotWebConf *webConf) {
    webConf->addParameter(brightnessParam);
    webConf->addParameter(ledCountParam);
}

boolean LedWebConfig::validate(WebServer *server) {
    boolean valid = true;

    if (server->arg(this->brightnessParam->getId()).length() == 0) {
        this->brightnessParam->errorMessage = "Please provide the brightness value.";
        valid = false;
    }

    if (server->arg(this->ledCountParam->getId()).length() == 0) {
        this->ledCountParam->errorMessage = "Please provide the LED count.";
        valid = false;
    }

    return valid;
}

void LedWebConfig::displayConfig(Logger *logger) {
    logger->print("Brightness: ");
    logger->println(this->brightness);
    logger->print("LED count: ");
    logger->println(this->ledCount);
}

int LedWebConfig::getBrightness() {
  return String(this->brightness).toInt();
}

int LedWebConfig::getLedCount() {
  return String(this->ledCount).toInt();
}
#endif