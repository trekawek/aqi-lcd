
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

#include "interface.h"
#include "timage.h"

#include "bitmaps/icon-humidity.h"
#include "bitmaps/icon-pm10.h"
#include "bitmaps/icon-pm25.h"
#include "bitmaps/icon-pressure.h"
#include "bitmaps/icon-temp.h"

#define BLACK 0x0000
#define WHITE 0xFFFF

#define INDICATOR_RADIUS 4
#define INDICATOR_LENGTH 40
#define INDICATOR_COLOR 0x0339

static const int PM25_LEVELS[] = {0, 15, 30, 55, 110, 32768};
static const int PM10_LEVELS[] = {0, 25, 50, 90, 180, 32768};
static const int PM25_MAX = 25;
static const int PM10_MAX = 50;

int findThreshold(int v, const int levels[]) {
  for (int i = 0; ; i++) {
    if (levels[i] > v) {
      return i - 1;
    }
  }
}

int getIndex(const displayModel *model) {
  int pm25Index = findThreshold(model->pm25, PM25_LEVELS);
  int pm10Index = findThreshold(model->pm10, PM10_LEVELS);
  return max(pm25Index, pm10Index);
}

void drawLevels(Adafruit_ILI9341 *tft, uint16_t x, uint16_t y) {
  tft->fillCircle(x, y, 70, INDICATOR_COLOR);
  
  uint16_t colors[] = {0x2d24, 0xa644, 0xff66, 0xfd65, 0xf963};
  
  uint16_t x2 = x - 60;
  uint16_t y2 = y;

  for (float i = 0; i < 5; i += 0.1) {
    float angle = PI * i / 5;
    
    uint16_t x3 = sin(PI + HALF_PI - angle) * 60 + x;
    uint16_t y3 = cos(PI + HALF_PI - angle) * 60 + y;

    tft->fillTriangle(x, y, x2, y2, x3, y3, colors[(int)i]);

    x2 = x3;
    y2 = y3;
  }
  
  tft->fillCircle(x, y, 20, BLACK);
  tft->fillRect(x - 70, y, 150, 70, BLACK);
}

void drawIndicator(Adafruit_ILI9341 *tft, float percent, uint16_t x, uint16_t y) {
  float angle = percent * PI;
  tft->fillCircle(x, y, INDICATOR_RADIUS, INDICATOR_COLOR);

  uint16_t x1 = sin(-angle) * (INDICATOR_RADIUS - 2) + x;
  uint16_t y1 = cos(-angle) * (INDICATOR_RADIUS - 2) + y;

  uint16_t x2 = sin(-angle + PI) * (INDICATOR_RADIUS - 2) + x;
  uint16_t y2 = cos(-angle + PI) * (INDICATOR_RADIUS - 2) + y;

  uint16_t x3 = sin(PI + HALF_PI - angle) * INDICATOR_LENGTH + x;
  uint16_t y3 = cos(PI + HALF_PI - angle) * INDICATOR_LENGTH + y;

  tft->fillTriangle(x1, y1, x2, y2, x3, y3, INDICATOR_COLOR);
}

void drawBitmap(Adafruit_ILI9341 *tft, uint16_t x, uint16_t y, const tImage *image) {
  uint16_t x0, y0;
  const uint16_t *pdata = image->data;
  for (y0 = 0; y0 < image->height; y0++) {
    for (x0 = 0; x0 < image->width; x0++) {
      tft->drawPixel(x + x0, y + y0, *pdata++);
    }
  }
}

void drawScreen(Adafruit_ILI9341 *tft, displayModel *model) {
  int pm25rel = model->pm25 * 100 / PM25_MAX;
  int pm10rel = model->pm10 * 100 / PM10_MAX;
  int index = getIndex(model);
  
  tft->fillScreen(0);

  drawLevels(tft, 120, 75);
  
  float percent[] = {0.1, 0.3, 0.5, 0.7, 0.9};
  drawIndicator(tft, percent[index], 120, 75);
  
  tft->setTextColor(WHITE);
  tft->setTextSize(1);

  // pm 2.5
  tft->setCursor(55, 100);
  tft->setFont(&FreeSans12pt7b);
  tft->print(model->pm25);
  tft->setFont(&FreeSans9pt7b);
  tft->print("ug/m3");

  tft->setFont(&FreeSans12pt7b);
  tft->setCursor(145, 105);
  tft->print(pm25rel);
  tft->print("%");

  // pm 10
  tft->setCursor(55, 150);
  tft->setFont(&FreeSans12pt7b);
  tft->print(model->pm10);
  tft->setFont(&FreeSans9pt7b);
  tft->print("ug/m3");

  tft->setFont(&FreeSans12pt7b);
  tft->setCursor(145, 150);
  tft->print(pm10rel);
  tft->print("%");

  // temp
  tft->setCursor(90, 200);
  tft->print(model->temp);
  tft->print("'C");

  // humidity
  tft->setCursor(90, 250);
  tft->print(model->humidity);
  tft->print("%");

  // pressure
  tft->setCursor(90, 300);
  tft->print(model->pressure);
  tft->print(" hPa");

  drawBitmap(tft, 6, 79, &iconpm25);
  drawBitmap(tft, 5, 129, &iconpm10);
  drawBitmap(tft, 7, 174, &icontemp);
  drawBitmap(tft, 3, 227, &iconhumidity);
  drawBitmap(tft, 3, 275, &iconpressure);
}
