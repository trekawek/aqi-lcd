#if FRONTEND_LCD
#include "lcd/display-clock.h"
#include "lcd/interface.h"

DisplayClock::DisplayClock(TFT_eSPI *tft, int timezoneOffset) {
  this->ntpUDP = new WiFiUDP();
  this->timeClient = new NTPClient(*ntpUDP, "pool.ntp.org", timezoneOffset * 3600);
  this->tft = tft;
}

void DisplayClock::update() {
  this->timeClient->update();
  long epochTime = this->timeClient->getEpochTime();
  if (this->lastEpochTime != epochTime) {
    this->drawTime(this->timeClient->getFormattedTime());
  }
  this->lastEpochTime = epochTime;
}

void DisplayClock::drawTime(String time) {
  tft->fillRect(160, 3, 80, 20, TFT_BLACK);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(1);
  tft->setCursor(165, 17);
  tft->setFreeFont(&FreeSans9pt7b);
  tft->print(time);
}
#endif