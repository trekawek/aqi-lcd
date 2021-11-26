#if FRONTEND_LED_MATRIX
#ifndef _LED_MATRIX_FRONTEND_H
#define _LED_MATRIX_FRONTEND_H

#include <Arduino.h>
#include <PxMatrix.h>
#include <Ticker.h>

#include "data-source.h"
#include "frontend.h"
#include "led-matrix/led-matrix-web-config.h"

class LedMatrixFrontend : public Frontend {
    public:
    LedMatrixFrontend();

    CustomWebConfig* getCustomWebConfig();
    Logger* getLogger();

    void init();
    void connected(Config config, DataSource *dataSource);
    void doLoop();

    void updateDisplayModel(DisplayModel *displayModel);
    void updateDataSourceStatus(DataSourceStatus status);

    private:
   
    LedMatrixWebConfig *ledMatrixWebConfig;
    Logger *logger;
    PxMATRIX *ledmatrix;
    Ticker *display_ticker;
    
};

#endif
#endif