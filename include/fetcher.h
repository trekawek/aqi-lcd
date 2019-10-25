#ifndef _FETCHER_H
#define _FETCHER_H

#include <Arduino.h>
#include <TFT_eSPI.h>

void initFetcher(String sensorUrlParam, SensorType sensorTypeParam);

void updateDisplay(TFT_eSPI *tft);

#endif