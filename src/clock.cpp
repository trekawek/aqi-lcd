#include <NTPClient.h>
#include <WiFiUdp.h>

#include "clock.h"
#include "interface.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0);

long lastEpochTime = 0;

void initClock(int timezoneOffset) {
  timeClient.setTimeOffset(timezoneOffset);
}

void updateClock(Adafruit_ILI9341 *tft) {
  timeClient.update();
  long epochTime = timeClient.getEpochTime();
  if (lastEpochTime != epochTime) {
    drawTime(tft, timeClient.getFormattedTime());
  }
  lastEpochTime = epochTime;
}
