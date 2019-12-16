#if FRONTEND_LCD
#include "lcd/lcd-frontend.h"

LcdFrontend::LcdFrontend() {
    tft = new TFT_eSPI();
}

void LcdFrontend::init() {
  tft->begin();
  tft->setRotation(0);
  tft->fillScreen(0);
}

void LcdFrontend::connected(Config config, DataSource *dataSource) {
  tft->fillScreen(0);
  displayClock = new DisplayClock(tft, config.timeZoneOffset);
  localMeasure = new LocalMeasure(tft, config.sensorAltitude);
  interface = new Interface(tft, localMeasure);
  touchInterface = new TouchInterface(tft, interface);
  wifiStatus = new WifiStatus(tft);
}

void LcdFrontend::doLoop() {
  displayClock->update();
  touchInterface->update();
  wifiStatus->update();
}

void LcdFrontend::updateDisplayModel(DisplayModel *displayModel) {
  interface->update(displayModel);
}

void LcdFrontend::updateDataSourceStatus(DataSourceStatus status) {
  uint32_t color = TFT_BLACK;
  switch (status) {
    case SUCCESS:
    color = TFT_GREEN;
    break;

    case FAILURE:
    color = TFT_RED;
    break;

    case IN_PROGRESS:
    color = TFT_YELLOW;
    break;
 }
 tft->fillCircle(30, 10, 3, color);
}

void LcdFrontend::print(String message) {
  tft->print(message);
}

void LcdFrontend::println(String message) {
  tft->println(message);
}
#endif