#ifdef FRONTEND_LED_MATRIX

#include "led-matrix/led-matrix-web-config.h"

LedMatrixWebConfig::LedMatrixWebConfig() {
    this->brightnessParam = new IotWebConfParameter("Brightness", "brightness", this->brightness, 5, "number", NULL, "32", "min=\"0\" max=\"255\"");

}

void LedMatrixWebConfig::addParameters(IotWebConf *webConf) {
    webConf->addParameter(brightnessParam);
}

boolean LedMatrixWebConfig::validate(WebServer *server) {
    boolean valid = true;

    if (server->arg(this->brightnessParam->getId()).length() == 0) {
        this->brightnessParam->errorMessage = "Please provide the brightness value.";
        valid = false;
    }

    return valid;
}

void LedMatrixWebConfig::displayConfig(Logger *logger) {
    logger->print("Brightness: ");
    logger->println(this->brightness);
}

int LedMatrixWebConfig::getBrightness() {
  return String(this->brightness).toInt();
}

#endif