#if FRONTEND_LED
#ifndef _LED_FRONTEND_H
#define _LED_FRONTEND_H

#include <Arduino.h>

#include "data-source.h"
#include "frontend.h"

class LedFrontend : public Frontend {
    public:
    LedFrontend();
    void init();
    void connected(Config config, DataSource *dataSource);
    void doLoop();

    void updateDisplayModel(DisplayModel *displayModel);
    void updateDataSourceStatus(DataSourceStatus status);
    void print(String message);
    void println(String message);
};

#endif
#endif