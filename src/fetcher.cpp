#include <Arduino.h>

#include "data-source/aqi-eco.h"
#include "data-source/local.h"

#include "fetcher.h"
#include "interface.h"
#include "model.h"
#include "pollution-levels.h"

long lastDisplayUpdate = -60 * 1000;

String fetcherSensorUrl;
SensorType fetcherSensorType;

void initFetcher(String sensorUrl, SensorType sensorType) {
  fetcherSensorUrl = sensorUrl;
  fetcherSensorType = sensorType;
}

void createDisplayModel(JsonModel *json, DisplayModel *displayModel) {
  displayModel->pm10 = json->pm10;
  displayModel->pm25 = json->pm25;
  displayModel->temp = json->temp;
  displayModel->humidity = json->humidity;
  displayModel->pressure = json->pressure;
  displayModel->pm25rel = json->pm25 * 100 / PM25_MAX;
  displayModel->pm10rel = json->pm10 * 100 / PM10_MAX;
  displayModel->level = getLevel(json);
}

void updateDisplay(TFT_eSPI *tft) {
  if (millis() - lastDisplayUpdate > 60 * 1000) {
    JsonModel json;
    
    Serial.println("Updating sensor values");
    switch (fetcherSensorType) {
        case AQI_ECO:
        Serial.println("Fetching from aqi.eco: " + fetcherSensorUrl);
        getFromAqiEco(fetcherSensorUrl, &json);
        break;

        case LOCAL_DEVICE:
        Serial.println("Fetching from local device: " + fetcherSensorUrl);
        getFromLocalDevice(fetcherSensorUrl, &json);
        break;

        default:
        Serial.println("Invalid sensor type");
        return;
    }

    DisplayModel displayModel;
    createDisplayModel(&json, &displayModel);
    drawScreen(tft, &displayModel);
    lastDisplayUpdate = millis();
  }
}
