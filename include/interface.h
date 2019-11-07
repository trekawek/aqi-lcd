#ifndef _INTERFACE_H
#define _INTERFACE_H

#include <TFT_eSPI.h>

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

class Interface {
  public:
  Interface(TFT_eSPI *tft);
  void update(DisplayModel *model);

  void drawTouchPosition(uint16_t x, uint16_t y, uint16_t z);
  void clearTouchPosition();

  private:
  TFT_eSPI *tft;
  boolean initialDraw = true;
  DisplayModel previousModel = {0};

  void drawLevels(uint16_t x, uint16_t y);
  void drawIndicator(float percent, uint16_t x, uint16_t y);
  void drawBitmap(uint16_t x, uint16_t y, const tImage *image);

  static void unpack(uint16_t color, uint8_t *colors);
  static uint16_t pack(uint8_t *colors);
  static uint16 mixColors(uint16_t c1, uint16_t c2, float f);
  static boolean isDifferent(float f1, float f2);
};

#endif