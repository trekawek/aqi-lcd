#if FRONTEND_LED
#include "led/led-frontend.h"

LedFrontend::LedFrontend() {
}

void LedFrontend::init() {
}

void LedFrontend::connected(Config config, DataSource *dataSource) {
}

void LedFrontend::doLoop() {
}

void LedFrontend::updateDisplayModel(DisplayModel *displayModel) {
}

void LedFrontend::updateDataSourceStatus(DataSourceStatus status) {
}

void LedFrontend::print(String message) {
  Serial.print(message);
}

void LedFrontend::println(String message) {
  Serial.println(message);
}

#endif