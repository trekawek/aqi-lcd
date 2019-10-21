#ifndef _MODEL_H
#define _MODEL_H

#include <stdint.h>

typedef struct {
  uint16_t pm25 = 0;
  uint16_t pm10 = 0;
  uint16_t temp = 0;
  uint16_t humidity = 0;
  uint16_t pressure = 0;
} JsonModel;

#endif