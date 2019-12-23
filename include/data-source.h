#ifndef _DATA_SOURCE_H
#define _DATA_SOURCE_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "mdns-resolver.h"
#include "model.h"

class DataSource {
    public:
    static DataSource* createDataSource(SensorType sensorType, String sensorUrl, MDNSResolver *mdnsResolver);
    virtual boolean readModel(JsonModel *model);

    protected:
    String url;
};

#endif