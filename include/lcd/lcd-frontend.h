#if FRONTEND_LCD
#ifndef _LCD_FRONTEND_H
#define _LCD_FRONTEND_H

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "data-source.h"
#include "frontend.h"

#include "lcd/local-measure.h"
#include "lcd/display-clock.h"
#include "lcd/interface.h"
#include "lcd/touch-interface.h"
#include "lcd/wifi-status.h"

class LcdFrontend : public Frontend {
    public:
    LcdFrontend();
    void init();
    void connected(Config config, DataSource *dataSource);
    void doLoop();

    void updateDisplayModel(DisplayModel *displayModel);
    void updateDataSourceStatus(DataSourceStatus status);
    void print(String message);
    void println(String message);

    private:
    TFT_eSPI *tft;
    DisplayClock *displayClock;
    Interface *interface;
    TouchInterface *touchInterface;
    WifiStatus *wifiStatus;
    LocalMeasure *localMeasure;
};

#endif
#endif