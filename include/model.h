#ifndef _MODEL_H
#define _MODEL_H

#include <stdint.h>

typedef struct {
  uint16_t pm25;
  uint16_t pm10;
  uint16_t temp;
  uint16_t humidity;
  uint16_t pressure;
} JsonModel;

#endif