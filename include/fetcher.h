#ifndef _FETCHER_H
#define _FETCHER_H

#include <Arduino.h>

#include "data-source.h"
#include "frontend.h"
#include "model.h"

#define INTERVAL_SEC 60

class Fetcher {
    public:
    Fetcher(Frontend *frontend, DataSource *dataSource);
    boolean update();

    private:
    DataSource *dataSource;
    Frontend *frontend;
    long lastDisplayUpdate;

    static void createDisplayModel(JsonModel *json, DisplayModel *displayModel);
};

#endif