#if FRONTEND_LCD
#include "lcd/lcd-frontend.h"
#include "lcd/lcd-web-config.h"

LcdFrontend::LcdFrontend() {
  tft = new TFT_eSPI();
  logger = new LcdLogger(tft);
  lcdWebConfig = new LcdWebConfig();
}

CustomWebConfig* LcdFrontend::getCustomWebConfig() {
  return lcdWebConfig;
}

 Logger* LcdFrontend::getLogger() {
   return logger;
 }

void LcdFrontend::init() {
  tft->begin();
  tft->setRotation(0);
  tft->fillScreen(0);
}

void LcdFrontend::connected(Config config, DataSource *dataSource) {
  tft->fillScreen(0);
  displayClock = new DisplayClock(tft, lcdWebConfig->getTimezoneOffset());
  interface = new Interface(tft);
  backlight = new Backlight(lcdWebConfig->getBacklightTime());
  touchInterface = new TouchInterface(tft, interface, backlight);
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

#endif