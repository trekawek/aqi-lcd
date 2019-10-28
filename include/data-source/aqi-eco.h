#ifndef _AQI_ECO_DATA_SOURCE_H
#define _AQI_ECO_DATA_SOURCE_H

#include <Arduino.h>
#include "model.h"
#include "data-source.h"

class AqiEcoDataSource : public DataSource {
    public:
    AqiEcoDataSource(String url);
    void readModel(JsonModel *model);
};

#endif