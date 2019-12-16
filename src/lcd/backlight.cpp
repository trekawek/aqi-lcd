#if FRONTEND_LCD
#include <Arduino.h>

#include "lcd/backlight.h"

Backlight::Backlight(unsigned long backlightTime) {
  this->backlightTime = backlightTime;

  setBacklight(true);
}

void Backlight::setBacklight(boolean backlight) {
  if (backlight) {
    digitalWrite(D3, LOW);
    this->lastUpdate = millis();
  } else {
    digitalWrite(D3, HIGH);
  }
}
#endif