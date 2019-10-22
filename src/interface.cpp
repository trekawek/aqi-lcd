#include <Arduino.h>
#include <Adafruit_GFX.h>

#include "interface.h"

#include "bitmaps/icon-humidity.h"
#include "bitmaps/icon-pm10.h"
#include "bitmaps/icon-pm25.h"
#include "bitmaps/icon-pressure.h"
#include "bitmaps/icon-temp.h"

#define INDICATOR_RADIUS 4
#define INDICATOR_LENGTH 40
#define INDICATOR_COLOR 0x0339

void unpack(uint16_t color, uint8_t *colors) {
  colors[0] = (color >> 11) & 0x1f;
  colors[1] = (color >> 5) & 0x3f;
  colors[2] = (color >> 0) & 0x1f;
}

uint16_t pack(uint8_t *colors) {
  uint16_t r = colors[0];
  uint16_t g = colors[1];
  uint16_t b = colors[2];
  return (r << 11) | (g << 5) | b;
}

uint16 mixColors(uint16_t c1, uint16_t c2, float f) {
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

void drawLevels(Adafruit_ILI9341 *tft, uint16_t x, uint16_t y) {
  tft->fillCircle(x, y, 65, INDICATOR_COLOR);
  
  uint16_t colors[] = {0x0400, 0x07e0, 0xffe0, 0xfd65, 0xf963, 0x9000};
  
  uint16_t x2 = x - 60;
  uint16_t y2 = y;

  for (float i = 0; i < 5; i += 0.1) {
    float angle = PI * i / 5;
    
    uint16_t x3 = sin(PI + HALF_PI - angle) * 60 + x;
    uint16_t y3 = cos(PI + HALF_PI - angle) * 60 + y;

    uint16 c = mixColors(colors[(int) i], colors[(int) i + 1], i - ((int) i));
    tft->fillTriangle(x, y, x2, y2, x3, y3, c);

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

void drawScreen(Adafruit_ILI9341 *tft, DisplayModel *model) {
  tft->fillScreen(0);

  drawLevels(tft, 120, 75);
  drawIndicator(tft, model->level, 120, 75);
  
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
  tft->print(model->pm25rel);
  tft->print("%");

  // pm 10
  tft->setCursor(55, 150);
  tft->setFont(&FreeSans12pt7b);
  tft->print(model->pm10);
  tft->setFont(&FreeSans9pt7b);
  tft->print("ug/m3");

  tft->setFont(&FreeSans12pt7b);
  tft->setCursor(145, 150);
  tft->print(model->pm10rel);
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
