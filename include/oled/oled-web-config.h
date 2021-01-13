#if FRONTEND_OLED
#ifndef _OLED_WEB_CONFIG_H
#define _OLED_WEB_CONFIG_H

#include "frontend.h"

class OledWebConfig : public CustomWebConfig {
    public:
    OledWebConfig();
    void addParameters(IotWebConf *webConf);
    boolean validate(WebServer *server);
    void displayConfig(Logger *logger);
};

#endif
#endif