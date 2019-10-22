#include <Arduino.h>

#include "data-source/aqi-eco.h"
#include "data-source/local.h"

#include "fetcher.h"
#include "interface.h"
#include "model.h"
#include "pollution-levels.h"

long lastDisplayUpdate = 0;

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

void updateDisplay(Adafruit_ILI9341 *tft) {
  if (millis() - lastDisplayUpdate > 60 * 1000) {
    JsonModel json;
    
    switch (fetcherSensorType) {
        case AQI_ECO:
        getFromAqiEco(fetcherSensorUrl, &json);
        break;

        case LOCAL_DEVICE:
        getFromLocalDevice(fetcherSensorUrl, &json);
        break;
    }

    DisplayModel displayModel;
    createDisplayModel(&json, &displayModel);
    drawScreen(tft, &displayModel);
    lastDisplayUpdate = millis();
  }
}
