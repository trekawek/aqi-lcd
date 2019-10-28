#include "data-source.h"
#include "data-source/aqi-eco.h"
#include "data-source/local.h"

DataSource* DataSource::createDataSource(SensorType sensorType, String sensorUrl) {
    switch (sensorType) {
        case AQI_ECO:
        Serial.println("Fetching from aqi.eco: " + sensorUrl);
        return new AqiEcoDataSource(sensorUrl);

        case LOCAL_DEVICE:
        Serial.println("Fetching from local device: " + sensorUrl);
        return new LocalDataSource(sensorUrl);
    }
    Serial.println("Invalid sensor type");
    return NULL;
}