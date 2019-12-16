#if FRONTEND_LCD
#ifndef _MEASURE_H
#define _MEASURE_H

#include <TFT_eSPI.h>
#include <Adafruit_BME280.h>

class LocalMeasure {
  public:
  LocalMeasure(TFT_eSPI *tft, int sensorAltitude);
  void fetchSensorBME280();
  float getTemperature();
  float getHumidity();
  float getPressure();
  bool bme280_init_failed = false;

  private:
  TFT_eSPI *tft;
  Adafruit_BME280 bme280;

  int sensorAltitude;
  float last_value_BME280_T = -128.0;
  float last_value_BME280_P = -1.0;
  float last_value_BME280_H = -1.0;

  bool initBME280(char addr);
  float normalizePressure(float pressure, float temperature);
};

#endif
#endif
