#include <Arduino.h>

#include "data-source/aqi-eco.h"
#include "data-source/local.h"

#include "fetcher.h"
#include "pollution-levels.h"

Fetcher::Fetcher(Frontend *frontend, DataSource *dataSource) {
  this->dataSource = dataSource;
  this->frontend = frontend;
}

boolean Fetcher::update() {
  if (millis() - this->lastDisplayUpdate > 60 * 1000) {
    JsonModel json;
    Serial.println("Updating sensor values");
    frontend->updateDataSourceStatus(IN_PROGRESS);
    if (this->dataSource->readModel(&json)) {
      DisplayModel displayModel;
      createDisplayModel(&json, &displayModel);
      frontend->updateDisplayModel(&displayModel);
      this->lastDisplayUpdate = millis();
      frontend->updateDataSourceStatus(SUCCESS);
      return true;
    } else {
      frontend->updateDataSourceStatus(FAILURE);
      return false;
    }
  }
  return true;
}

void Fetcher::createDisplayModel(JsonModel *json, DisplayModel *displayModel) {
  displayModel->pm10 = json->pm10;
  displayModel->pm25 = json->pm25;
  displayModel->temp = json->temp;
  displayModel->humidity = json->humidity;
  displayModel->pressure = json->pressure;
  displayModel->pm25rel = json->pm25 * 100 / PollutionLevels::PM25_MAX;
  displayModel->pm10rel = json->pm10 * 100 / PollutionLevels::PM10_MAX;
  displayModel->level = PollutionLevels::getLevel(json);
}
