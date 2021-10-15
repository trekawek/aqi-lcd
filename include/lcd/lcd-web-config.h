#if FRONTEND_LCD
#ifndef _LCD_WEB_CONFIG_H
#define _LCD_WEB_CONFIG_H

#include "frontend.h"

class LcdWebConfig : public CustomWebConfig {
    public:
    LcdWebConfig();
    void addParameters(IotWebConf *webConf);
    boolean validate(WebServer *server);
    void displayConfig(Logger *logger);
    
    int getTimezoneOffset();
    int getBacklightTime();

    private:
    char timezoneOffset[5];
    char backlightTime[5];

    IotWebConfParameter *timezoneOffsetParam;
    IotWebConfParameter *backlightTimeParam;
};

#endif
#endif