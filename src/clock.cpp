#include <NTPClient.h>
#include <WiFiUdp.h>

#include "clock.h"
#include "interface.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0);

long lastEpochTime = 0;

void drawTime(Adafruit_ILI9341 *tft, String time) {
  tft->fillRect(160, 3, 80, 20, BLACK);
  tft->setTextColor(WHITE);
  tft->setTextSize(1);
  tft->setCursor(165, 17);
  tft->setFont(&FreeSans9pt7b);
  tft->print(time);
}

void initClock(int timezoneOffset) {
  timeClient.setTimeOffset(timezoneOffset * 3600);
}

void updateClock(Adafruit_ILI9341 *tft) {
  timeClient.update();
  long epochTime = timeClient.getEpochTime();
  if (lastEpochTime != epochTime) {
    drawTime(tft, timeClient.getFormattedTime());
  }
  lastEpochTime = epochTime;
}
