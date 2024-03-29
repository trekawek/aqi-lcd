#ifndef _AQI_ECO_DATA_SOURCE_H
#define _AQI_ECO_DATA_SOURCE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiClientSecureBearSSL.h>
#include "model.h"
#include "data-source.h"

class AqiEcoDataSource : public DataSource {
    public:
    AqiEcoDataSource(String url);
    boolean readModel(JsonModel *model);
    boolean isReady();

    private:
    BearSSL::WiFiClientSecure *client;
    StaticJsonDocument<1536> doc;
};

#endif