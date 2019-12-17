#if FRONTEND_LCD
#include "lcd/local-measure.h"
#include "lcd/interface.h"

LocalMeasure::LocalMeasure(TFT_eSPI *tft, int sensorAltitude) {
  this->tft = tft;
  this->bme280 = bme280;
  this->sensorAltitude = sensorAltitude;

  if (! initBME280(0x76) && ! initBME280(0x77)) {
    tft->fillScreen(0);
    tft->println("Check BME280 wiring!");
    bme280_init_failed = true;
  }
}

bool LocalMeasure::initBME280(char addr) {
  if (bme280.begin(addr)) {
    bme280.setSampling(
      Adafruit_BME280::MODE_NORMAL,
      Adafruit_BME280::SAMPLING_X2,
      Adafruit_BME280::SAMPLING_X16,
      Adafruit_BME280::SAMPLING_X1,
      Adafruit_BME280::FILTER_X16,
      Adafruit_BME280::STANDBY_MS_0_5);
    return true;
  } else {
    return false;
  }
}

void LocalMeasure::fetchSensorBME280() {
  const auto t = bme280.readTemperature();
  const auto p = bme280.readPressure();
  const auto h = bme280.readHumidity();
  if (isnan(t) || isnan(h) || isnan(p)) {
    last_value_BME280_T = -128.0;
    last_value_BME280_P = -1.0;
    last_value_BME280_H = -1.0;
    tft->fillScreen(0);
    tft->println("BME280 read failed!");
  } else {
    last_value_BME280_T = t;
    last_value_BME280_P = p;
    last_value_BME280_H = h;
  }
}

float LocalMeasure::normalizePressure(float pressure, float temperature) {
  if (isnan(pressure)) {
    return 0;
  }
  if (sensorAltitude == 0) {
    return pressure;
  }

  float mu = 0.0289644;
  float g = 9.80665;
  float R = 8.3144598;
  float T = temperature + 273.15;
  float normalized = pressure / exp(- mu * g * sensorAltitude / (R * T));
  return normalized;
}

float LocalMeasure::getTemperature() {
  return last_value_BME280_T;
}

float LocalMeasure::getHumidity() {
  return last_value_BME280_H;
}

float LocalMeasure::getPressure() {
  return normalizePressure((last_value_BME280_P / 100), last_value_BME280_T);
}

#endif
