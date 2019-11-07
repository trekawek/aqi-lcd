#ifndef _DISPLAY_CLOCK_H
#define _DISPLAY_CLOCK_H

#include <NTPClient.h>
#include <TFT_eSPI.h>
#include <WiFiUdp.h>

class DisplayClock {
    public:
    DisplayClock(TFT_eSPI *tft, int timezoneOffset);
    void update();

    private:
    WiFiUDP *ntpUDP;
    NTPClient *timeClient;
    TFT_eSPI *tft;
    long lastEpochTime;

    void drawTime(String time);
};

#endif