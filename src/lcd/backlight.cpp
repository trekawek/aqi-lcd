#if FRONTEND_LCD
#include <Arduino.h>

#include "lcd/backlight.h"

Backlight::Backlight(unsigned long backlightTime) {
  this->backlightTime = backlightTime;

  setBacklight(true);
}

void Backlight::update() {
  if (millis() - this->lastUpdate > this->backlightTime * 1000) {
    setBacklight(false);
  }
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