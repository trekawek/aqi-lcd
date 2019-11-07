#include "touch-interface.h"

TouchInterface::TouchInterface(TFT_eSPI *tft, Interface *interface) {
  this->tft = tft;
  this->interface = interface;
}

void TouchInterface::update() {
  uint16_t x, y, z;
  if (tft->getTouch(&x, &y, 150)) {
    z = tft->getTouchRawZ();
    interface->drawTouchPosition(x, y, z);
    touchDisplayed = true;
  } else if (touchDisplayed) {
    interface->clearTouchPosition();
    touchDisplayed = false;
  }
}