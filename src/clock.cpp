#include <NTPClient.h>
#include <WiFiUdp.h>

#include "clock.h"
#include "interface.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0);

long lastEpochTime = 0;

void drawTime(TFT_eSPI *tft, String time) {
  tft->fillRect(160, 3, 80, 20, TFT_BLACK);
  tft->setTextColor(TFT_WHITE);
  tft->setTextSize(1);
  tft->setCursor(165, 17);
  tft->setFreeFont(&FreeSans9pt7b);
  tft->print(time);
}

void initClock(int timezoneOffset) {
  timeClient.setTimeOffset(timezoneOffset * 3600);
}

void updateClock(TFT_eSPI *tft) {
  timeClient.update();
  long epochTime = timeClient.getEpochTime();
  if (lastEpochTime != epochTime) {
    drawTime(tft, timeClient.getFormattedTime());
  }
  lastEpochTime = epochTime;
}
