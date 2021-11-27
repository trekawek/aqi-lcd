#if FRONTEND_LED_MATRIX
#ifndef _LED_MATRIX_WEB_CONFIG_H
#define _LED_MATRIX_WEB_CONFIG_H

#include "frontend.h"

class LedMatrixWebConfig : public CustomWebConfig {
    public:
    LedMatrixWebConfig();
    void addParameters(IotWebConf *webConf);
    boolean validate(WebServer *server);
    void displayConfig(Logger *logger);

    int getBrightness();
    // int getLedCount();

    private:
    char brightness[5];
    // char ledCount[6];

    IotWebConfParameter *brightnessParam;
    // IotWebConfParameter *ledCountParam;
};

#endif
#endif