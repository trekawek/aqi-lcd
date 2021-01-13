#ifdef FRONTEND_OLED

#include "oled/oled-web-config.h"

OledWebConfig::OledWebConfig() {
}

void OledWebConfig::addParameters(IotWebConf *webConf) {
}

boolean OledWebConfig::validate(WebServer *server) {
    return true;
}

void OledWebConfig::displayConfig(Logger *logger) {
}
#endif