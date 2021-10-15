#if FRONTEND_LCD
#include "lcd/touch-interface.h"

TouchInterface::TouchInterface(TFT_eSPI *tft, Interface *interface, Backlight *backlight) {
  this->tft = tft;
  this->interface = interface;
  this->backlight = backlight;
}

void TouchInterface::update() {
  uint16_t x, y, z;

  backlight->update();

  if (tft->getTouch(&x, &y, 150)) {
    if (this->displayTouch) {
      z = tft->getTouchRawZ();
      interface->drawTouchPosition(x, y, z);
    }
    touchDisplayed = true;
    backlight->setBacklight(true);
  } else if (touchDisplayed) {
    if (this->displayTouch) {
      interface->clearTouchPosition();
    }
    touchDisplayed = false;
  }
}
#endif