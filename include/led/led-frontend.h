#if FRONTEND_LED
#ifndef _LED_FRONTEND_H
#define _LED_FRONTEND_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include "data-source.h"
#include "frontend.h"
#include "led/led-web-config.h"

class LedFrontend : public Frontend {
    public:
    LedFrontend();

    CustomWebConfig* getCustomWebConfig();
    Logger* getLogger();

    void init();
    void connected(Config config, DataSource *dataSource);
    void doLoop();

    void updateDisplayModel(DisplayModel *displayModel);
    void updateDataSourceStatus(DataSourceStatus status);

    private:
    Adafruit_NeoPixel *strip;

    LedWebConfig *ledWebConfig;
    Logger *logger;

    void unpack(uint32_t color, uint8_t *colors);
    uint32_t pack(uint8_t *colors);
    uint32_t mixColors(uint32_t c1, uint32_t c2, float f);
    uint32_t getColor(uint16_t ledIndex);
};

#endif
#endif