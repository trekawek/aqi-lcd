#if FRONTEND_LED
#include "led/led-frontend.h"
#include "serial-logger.h"
#include "led/led-web-config.h"

LedFrontend::LedFrontend() {
  this->strip = new Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
  this->ledWebConfig = new LedWebConfig();
  this->logger = new SerialLogger();
}

CustomWebConfig* LedFrontend::getCustomWebConfig() {
  return ledWebConfig;
}

Logger* LedFrontend::getLogger() {
  return logger;
}

void LedFrontend::init() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  strip->begin();
  strip->show();
  strip->setBrightness(BRIGHTNESS);
}

void LedFrontend::connected(Config config, DataSource *dataSource) {
 strip->setPixelColor(0, 0x00ff00);
 strip->show();
}

void LedFrontend::doLoop() {
}

void LedFrontend::updateDisplayModel(DisplayModel *displayModel) {
  uint16_t pixelLevel = displayModel->level * (strip->numPixels() - 1);
  for (int i = 1; i < strip->numPixels(); i++) {
    if (i <= pixelLevel) {
      uint32_t c = getColor(i);
      strip->setPixelColor(i, c);
    } else {
      strip->setPixelColor(i, 0);
    }
  }
  strip->show();
}

uint32_t LedFrontend::getColor(uint16_t ledIndex) {
  // hue range: ledIndex is mapped from (0, numPixels) to (100, 20°)
  int hue_deg = map(ledIndex, 0, strip->numPixels() - 1, 100, 20);
  uint16_t hue = ((float) hue_deg ) / 360.0 * 65535;
  return strip->gamma32(strip->ColorHSV(hue));
}

void LedFrontend::updateDataSourceStatus(DataSourceStatus status) {
  uint32_t color = 0x0;
  switch (status) {
    case SUCCESS:
    color = 0x00ff00;
    break;

    case FAILURE:
    color = 0xff0000;
    break;

    case IN_PROGRESS:
    color = 0xffff00;
    break;
 }
 strip->setPixelColor(0, color);
 strip->show();
}

void LedFrontend::unpack(uint32_t color, uint8_t *colors) {
  colors[0] = (color >> 16) & 0xff;
  colors[1] = (color >> 8) & 0xff;
  colors[2] = (color >> 0) & 0xff;
}

uint32_t LedFrontend::pack(uint8_t *colors) {
  uint16_t r = colors[0];
  uint16_t g = colors[1];
  uint16_t b = colors[2];
  return (r << 16) | (g << 8) | b;
}

uint32_t LedFrontend::mixColors(uint32_t c1, uint32_t c2, float f) {
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

#endif