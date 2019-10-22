#ifndef _CLOCK_H
#define _CLOCK_H

#include <Adafruit_ILI9341.h>

void initClock(int timezoneOffset);

void updateClock(Adafruit_ILI9341 *tft);

#endif