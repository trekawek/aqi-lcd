#if FRONTEND_LED
#ifndef _LED_WEB_CONFIG_H
#define _LED_WEB_CONFIG_H

#include "frontend.h"

class LedWebConfig : public CustomWebConfig {
    public:
    LedWebConfig();
    void addParameters(IotWebConf *webConf);
    boolean validate(WebServer *server);
    void displayConfig(Logger *logger);
};

#endif
#endif