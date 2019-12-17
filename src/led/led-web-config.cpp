#ifdef FRONTEND_LED

#include "led/led-web-config.h"

LedWebConfig::LedWebConfig() {
}

void LedWebConfig::addParameters(IotWebConf *webConf) {
}

boolean LedWebConfig::validate(WebServer *server) {
    return true;
}

void LedWebConfig::displayConfig(Logger *logger) {
}

#endif