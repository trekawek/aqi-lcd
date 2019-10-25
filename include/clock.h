#ifndef _CLOCK_H
#define _CLOCK_H

#include <TFT_eSPI.h>

void initClock(int timezoneOffset);

void updateClock(TFT_eSPI *tft);

#endif