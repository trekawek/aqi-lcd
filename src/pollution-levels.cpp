#include <Arduino.h>

#include "pollution-levels.h"

const int PollutionLevels::PM25_LEVELS[] = {0, 15, 30, 55, 110};
const int PollutionLevels::PM10_LEVELS[] = {0, 25, 50, 90, 180};
const int PollutionLevels::PM25_MAX = 25;
const int PollutionLevels::PM10_MAX = 50;

float PollutionLevels::getLevel(const JsonModel *model) {
  float pm25Level = findThreshold(model->pm25, PM25_LEVELS);
  float pm10Level = findThreshold(model->pm10, PM10_LEVELS);
  return max(pm25Level, pm10Level);
}

float PollutionLevels::findThreshold(float v, const int levels[]) {
  float prevLevel = 0;
  for (int i = 1; i < 5; i++) {
    float currentLevel = levels[i];
    if (currentLevel > v) {
      return ((v - prevLevel) / (currentLevel - prevLevel) + i - 1) / 4;
    }
    prevLevel = currentLevel;
  }
  return 1.0F;
}
