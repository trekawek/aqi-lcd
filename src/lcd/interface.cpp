#if FRONTEND_LCD
#include <Arduino.h>

#include "lcd/interface.h"

#include "lcd/bitmaps/icon-humidity.h"
#include "lcd/bitmaps/icon-pm10.h"
#include "lcd/bitmaps/icon-pm25.h"
#include "lcd/bitmaps/icon-pressure.h"
#include "lcd/bitmaps/icon-temp.h"

#define INDICATOR_RADIUS 4
#define INDICATOR_LENGTH 40
#define INDICATOR_COLOR 0x0339

Interface::Interface(TFT_eSPI *tft) {
  this->tft = tft;
}

void Interface::update(DisplayModel *model) {
  boolean levelsRedrawn = false;
  if (this->initialDraw || isDifferent(this->previousModel.level, model->level)) {
    drawLevels(120, 95);
    drawIndicator(model->level, 120, 95);
    levelsRedrawn = true;
  }
  
  this->tft->setTextColor(TFT_WHITE);
  this->tft->setTextSize(1);

  int32_t y = 135;
  int32_t offset = 40;
  
  // pm 2.5
  if (levelsRedrawn || this->initialDraw || isDifferent(this->previousModel.pm25, model->pm25)) {
    this->tft->fillRect(55, y - 18, 185, offset - 15, TFT_BLACK);
    this->tft->setCursor(55, y);
    this->tft->setFreeFont(&FreeSans12pt7b);
    this->tft->print(model->pm25);
    this->tft->setFreeFont(&FreeSans9pt7b);
    this->tft->print("ug/m");
    this->tft->setCursor(this->tft->getCursorX(), y - 6);
    this->tft->print("3");
    this->tft->setCursor(this->tft->getCursorX(), y);
    this->tft->drawRect(this->tft->getCursorX() - 49, this->tft->getCursorY(), 2, 4, TFT_WHITE);

    this->tft->setFreeFont(&FreeSans12pt7b);
    this->tft->setCursor(145, y);
    this->tft->print(model->pm25rel);
    this->tft->print("%");
  }
  y += offset;

  // pm 10
  if (this->initialDraw || isDifferent(this->previousModel.pm10, model->pm10)) {
    this->tft->fillRect(55, y - 18, 185, offset - 15, TFT_BLACK);
    this->tft->setCursor(55, y);
    this->tft->setFreeFont(&FreeSans12pt7b);
    this->tft->print(model->pm10);
    this->tft->setFreeFont(&FreeSans9pt7b);
    this->tft->print("ug/m");
    this->tft->setCursor(this->tft->getCursorX(), y - 6);
    this->tft->print("3");
    this->tft->setCursor(this->tft->getCursorX(), y);
    this->tft->drawRect(this->tft->getCursorX() - 49, this->tft->getCursorY(), 2, 4, TFT_WHITE);

    this->tft->setFreeFont(&FreeSans12pt7b);
    this->tft->setCursor(145, y);
    this->tft->print(model->pm10rel);
    this->tft->print("%");
  }
  y += offset;

  // temp
  if (this->initialDraw || isDifferent(this->previousModel.temp, model->temp)) {
    this->tft->setFreeFont(&FreeSans12pt7b);
    this->tft->fillRect(55, y - 18, 185, offset - 15, TFT_BLACK);
    this->tft->setCursor(90, y);
    char temp[10];
    snprintf(temp, 10, "%.0f", model->temp);
    this->tft->print(temp);
    this->tft->print(" C");
    this->tft->drawCircle(this->tft->getCursorX() - 20, y - 15, 2, TFT_WHITE);
  }
  y += offset;

  // humidity
  if (this->initialDraw || isDifferent(this->previousModel.humidity, model->humidity)) {
    this->tft->setFreeFont(&FreeSans12pt7b);
    this->tft->fillRect(55, y - 18, 185, offset - 15, TFT_BLACK);
    this->tft->setCursor(90, y);
    this->tft->print(model->humidity);
    this->tft->print("%");
  }
  y += offset;

  // pressure
  if (this->initialDraw || isDifferent(this->previousModel.pressure, model->pressure)) {
    this->tft->setFreeFont(&FreeSans12pt7b);
    this->tft->fillRect(55, y - 18, 185, offset - 15, TFT_BLACK);
    this->tft->setCursor(90, y);
    this->tft->print(model->pressure);
    this->tft->print(" hPa");
  }

  y = 110;
  offset = 40;
  if (this->initialDraw) {
    drawBitmap(6, y, &iconpm25);
    drawBitmap(5, y += offset, &iconpm10);
    drawBitmap(7, y += offset, &icontemp);
    drawBitmap(3, y += offset, &iconhumidity);
    drawBitmap(3, y += offset, &iconpressure);
  }
  this->initialDraw = false;
  this->previousModel = *model;
}

void Interface::drawTouchPosition(uint16_t x, uint16_t y, uint16_t z) {
    tft->fillRect(0, 0, 58, 50, TFT_RED);
    tft->setTextColor(TFT_YELLOW);
    tft->setTextSize(1);
    tft->setCursor(0, 12);
    tft->print("X:");
    tft->print(x);
    tft->setCursor(0, 30);
    tft->print("Y:");
    tft->print(y);
    tft->setCursor(0, 48);
    tft->print("Z:");
    tft->print(z);
}

void Interface::clearTouchPosition() {
    tft->fillRect(0, 0, 58, 50, TFT_BLACK);
}

void Interface::drawLevels(uint16_t x, uint16_t y) {
  if (this->initialDraw) {
    this->tft->fillCircle(x, y, 65, INDICATOR_COLOR);
    this->tft->fillRect(x - 70, y, 150, 70, TFT_BLACK);
  }
  
  uint16_t colors[] = {0x0400, 0x07e0, 0xffe0, 0xfd65, 0xf963, 0x9000};
  
  uint16_t x2 = x - 60;
  uint16_t y2 = y;

  for (float i = 0; i < 5; i += 0.1) {
    float angle = PI * i / 5;
    
    uint16_t x3 = sin(PI + HALF_PI - angle) * 60 + x;
    uint16_t y3 = cos(PI + HALF_PI - angle) * 60 + y;

    uint16 c = mixColors(colors[(int) i], colors[(int) i + 1], i - ((int) i));
    this->tft->fillTriangle(x, y, x2, y2, x3, y3, c);

    x2 = x3;
    y2 = y3;
  }
  
  this->tft->fillCircle(x, y, 20, TFT_BLACK);
}

void Interface::drawIndicator(float percent, uint16_t x, uint16_t y) {
  float angle = percent * PI;
  this->tft->fillCircle(x, y, INDICATOR_RADIUS, INDICATOR_COLOR);

  uint16_t x1 = sin(-angle) * (INDICATOR_RADIUS - 2) + x;
  uint16_t y1 = cos(-angle) * (INDICATOR_RADIUS - 2) + y;

  uint16_t x2 = sin(-angle + PI) * (INDICATOR_RADIUS - 2) + x;
  uint16_t y2 = cos(-angle + PI) * (INDICATOR_RADIUS - 2) + y;

  uint16_t x3 = sin(PI + HALF_PI - angle) * INDICATOR_LENGTH + x;
  uint16_t y3 = cos(PI + HALF_PI - angle) * INDICATOR_LENGTH + y;

  this->tft->fillTriangle(x1, y1, x2, y2, x3, y3, INDICATOR_COLOR);
}

void Interface::drawBitmap(uint16_t x, uint16_t y, const tImage *image) {
  uint16_t x0, y0;
  const uint16_t *pdata = image->data;
  for (y0 = 0; y0 < image->height; y0++) {
    for (x0 = 0; x0 < image->width; x0++) {
      this->tft->drawPixel(x + x0, y + y0, pgm_read_byte(pdata++));
    }
  }
}

void Interface::unpack(uint16_t color, uint8_t *colors) {
  colors[0] = (color >> 11) & 0x1f;
  colors[1] = (color >> 5) & 0x3f;
  colors[2] = (color >> 0) & 0x1f;
}

uint16_t Interface::pack(uint8_t *colors) {
  uint16_t r = colors[0];
  uint16_t g = colors[1];
  uint16_t b = colors[2];
  return (r << 11) | (g << 5) | b;
}

uint16 Interface::mixColors(uint16_t c1, uint16_t c2, float f) {
  uint8_t rgb1[3];
  uint8_t rgb2[3];
  unpack(c1, rgb1);
  unpack(c2, rgb2);

  uint8_t rgb[3];
  for (int i = 0; i < 3; i++) {
    rgb[i] = (1 - f) * rgb1[i] + f * rgb2[i];
  }

  return pack(rgb);
}

boolean Interface::isDifferent(float f1, float f2) {
  return fabs(f1 - f2) > 0.001;
}
#endif