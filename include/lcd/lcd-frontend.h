#if FRONTEND_LCD
#ifndef _LCD_FRONTEND_H
#define _LCD_FRONTEND_H

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "data-source.h"
#include "frontend.h"

#include "lcd/backlight.h"
#include "lcd/display-clock.h"
#include "lcd/interface.h"
#include "lcd/lcd-logger.h"
#include "lcd/lcd-web-config.h"
#include "lcd/touch-interface.h"
#include "lcd/wifi-status.h"

class LcdFrontend : public Frontend {
    public:
    LcdFrontend();

    CustomWebConfig* getCustomWebConfig();
    Logger* getLogger();

    void init();
    void connected(Config config, DataSource *dataSource);
    void doLoop();

    void updateDisplayModel(DisplayModel *displayModel);
    void updateDataSourceStatus(DataSourceStatus status);

    private:
    TFT_eSPI *tft;
    DisplayClock *displayClock;
    Interface *interface;
    TouchInterface *touchInterface;
    Backlight *backlight;
    WifiStatus *wifiStatus;
    LcdWebConfig *lcdWebConfig;
    LcdLogger *logger;
};

#endif
#endif