#if FRONTEND_LCD
#ifndef _LCD_WIFI_STATUS_H
#define _LCD_WIFI_STATUS_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <TFT_eSPI.h>

class WifiStatus {
    public:
    WifiStatus(TFT_eSPI *tft);
    void update();

    private:
    TFT_eSPI *tft;
    int previousLevel = -1;
    boolean previousDataReceived = false;
    long lastUpdate = -60 * 1000;
};

#endif
#endif