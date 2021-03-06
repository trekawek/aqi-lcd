#if FRONTEND_LCD

#include "lcd/lcd-logger.h"

LcdLogger::LcdLogger(TFT_eSPI *tft) {
  this->tft = tft;
}

void LcdLogger::print(String message) {
  tft->print(message);
  Serial.print(message);
}

void LcdLogger::println(String message) {
  tft->println(message);
  Serial.println(message);
}

#endif