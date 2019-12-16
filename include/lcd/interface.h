#if FRONTEND_LCD
#ifndef _LCD_INTERFACE_H
#define _LCD_INTERFACE_H

#include <TFT_eSPI.h>

#include "model.h"
#include "lcd/local-measure.h"

typedef struct {
  const uint16_t *data;
  uint16_t width;
  uint16_t height;
  uint8_t  dataSize;
} tImage;

class Interface {
  public:
  Interface(TFT_eSPI *tft, LocalMeasure *measure);
  void update(DisplayModel *model);

  void drawTouchPosition(uint16_t x, uint16_t y, uint16_t z);
  void clearTouchPosition();
  LocalMeasure *measure;

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
#endif