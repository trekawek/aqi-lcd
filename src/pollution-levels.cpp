#include <Arduino.h>

#include "pollution-levels.h"

int findThreshold(int v, const int levels[]) {
  for (int i = 0; ; i++) {
    if (levels[i] > v) {
      return i - 1;
    }
  }
}

int getIndex(const JsonModel *model) {
  int pm25Index = findThreshold(model->pm25, PM25_LEVELS);
  int pm10Index = findThreshold(model->pm10, PM10_LEVELS);
  return max(pm25Index, pm10Index);
}
