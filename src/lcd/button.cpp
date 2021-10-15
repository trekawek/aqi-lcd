#if FRONTEND_LCD
#include "lcd/button.h"

Button::Button(Backlight *backlight) {
  this->backlight = backlight;
}

void Button::update() {
  if (analogRead(A0) > 768) {
      backlight->setBacklight(true);
  }
}
#endif