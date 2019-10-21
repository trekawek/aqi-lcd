
#include <Adafruit_ILI9341.h>

#include "model.h"

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

typedef struct {
  const uint16_t *data;
  uint16_t width;
  uint16_t height;
  uint8_t  dataSize;
} tImage;

void drawScreen(Adafruit_ILI9341 *tft, DisplayModel *model);

void drawTime(Adafruit_ILI9341 *tft, String time);