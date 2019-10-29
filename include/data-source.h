#ifndef _DATA_SOURCE_H
#define _DATA_SOURCE_H

#include <Arduino.h>
#include "model.h"

class DataSource {
    public:
    static DataSource* createDataSource(SensorType sensorType, String sensorUrl);
    virtual boolean readModel(JsonModel *model);

    protected:
    String url;
};

#endif