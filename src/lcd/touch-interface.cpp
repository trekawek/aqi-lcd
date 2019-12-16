#if FRONTEND_LCD
#include "lcd/touch-interface.h"

TouchInterface::TouchInterface(TFT_eSPI *tft, Interface *interface, unsigned long backlightTime) {
  this->tft = tft;
  this->interface = interface;
  this->backlightTime = backlightTime;

  setBacklight(true);
}

void TouchInterface::update() {
  uint16_t x, y, z;
  if (millis() - this->lastUpdate > (this->backlightTime * 1000)) {
    setBacklight(touchDisplayed);
  }
  if (tft->getTouch(&x, &y, 150)) {
    if (this->displayTouch) {
      z = tft->getTouchRawZ();
      interface->drawTouchPosition(x, y, z);
    }
    touchDisplayed = true;
    setBacklight(touchDisplayed);
  } else if (touchDisplayed) {
    if (this->displayTouch) {
      interface->clearTouchPosition();
    }
    touchDisplayed = false;
  }
}

void TouchInterface::setBacklight(boolean backlight) {
  if (backlight) {
    digitalWrite(D3, LOW);
    this->lastUpdate = millis();
  } else {
    digitalWrite(D3, HIGH);
  }
}
#endif