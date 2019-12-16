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

typedef struct {
  uint16_t pm25;
  uint16_t pm25rel;
  uint16_t pm10;
  uint16_t pm10rel;
  uint16_t temp;
  uint16_t humidity;
  uint16_t pressure;
  float level;
} DisplayModel;

typedef enum {
  AQI_ECO, LOCAL_DEVICE
} SensorType;

typedef struct {
  String sensorUrl;
  SensorType sensorType;
  int timeZoneOffset;
  int sensorAltitude;
} Config;

#endif