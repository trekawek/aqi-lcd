#ifndef _CLOCK_H
#define _CLOCK_H

//#include <Adafruit_ILI9341.h>
#include <TFT_eSPI.h>

void initClock(int timezoneOffset);

//void updateClock(Adafruit_ILI9341 *tft);
void updateClock(TFT_eSPI *tft);

#endif