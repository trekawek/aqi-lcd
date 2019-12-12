#if FRONTEND_LCD
#include "lcd/wifi-status.h"

WifiStatus::WifiStatus(TFT_eSPI *tft) {
  this->tft = tft;
}

void WifiStatus::update() {
  if (millis() - this->lastUpdate < 1000) {
    return;
  }
  float rssi = WiFi.RSSI();
  int level = map(constrain(rssi, -100, -50), -100, -50, 0, 4);
  if (level != this->previousLevel) {
    for (int i = 0; i < 5; i++) {
      uint16_t color = i <= level ? TFT_WHITE : TFT_DARKGREY; 
      tft->fillRect(5 + i * 4, 13 - i * 2, 3, 3 + i * 2, color);
    }
  }
  this->previousLevel = level;
  this->lastUpdate = millis();
}
#endif