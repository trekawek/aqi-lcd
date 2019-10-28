#ifndef _FETCHER_H
#define _FETCHER_H

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "data-source.h"
#include "interface.h"
#include "model.h"

class Fetcher {
    public:
    Fetcher(Interface *interface, DataSource *dataSource);
    void update();

    private:
    Interface *interface;
    DataSource *dataSource;
    long lastDisplayUpdate = -60 * 1000;

    static void createDisplayModel(JsonModel *json, DisplayModel *displayModel);
};

#endif