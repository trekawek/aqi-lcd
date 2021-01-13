#if FRONTEND_OLED
#include "oled/oled-frontend.h"
#include "serial-logger.h"

OledFrontend::OledFrontend() {
  this->oledWebConfig = new OledWebConfig();
  this->logger = new SerialLogger();
}

CustomWebConfig* OledFrontend::getCustomWebConfig() {
  return this->oledWebConfig;
}

Logger* OledFrontend::getLogger() {
  return logger;
}

void OledFrontend::init() {
}

void OledFrontend::connected(Config config, DataSource *dataSource) {
}

void OledFrontend::doLoop() {
}

void OledFrontend::updateDisplayModel(DisplayModel *displayModel) {
}

void OledFrontend::updateDataSourceStatus(DataSourceStatus status) {
}

#endif