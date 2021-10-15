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

    int getBrightness();
    int getLedCount();

    private:
    char brightness[5];
    char ledCount[6];

    IotWebConfParameter *brightnessParam;
    IotWebConfParameter *ledCountParam;
};

#endif
#endif