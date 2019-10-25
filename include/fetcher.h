#ifndef _FETCHER_H
#define _FETCHER_H

#include <Arduino.h>
//#include <Adafruit_ILI9341.h>
#include <TFT_eSPI.h>

void initFetcher(String sensorUrlParam, SensorType sensorTypeParam);

//void updateDisplay(Adafruit_ILI9341 *tft);
void updateDisplay(TFT_eSPI *tft);

#endif