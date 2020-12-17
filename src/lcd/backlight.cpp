#if FRONTEND_LCD
#include <Arduino.h>

#include "lcd/backlight.h"

Backlight::Backlight() {
}

void Backlight::begin() {
  pinMode(BACKLIGHT_PIN, OUTPUT);
  setBacklight(true);
}

void Backlight::setTimeout(unsigned long backlightTime) {
  this->backlightTime = backlightTime;
}

void Backlight::update() {
  if (enabled && this->backlightTime > 0 && millis() - this->lastUpdate > this->backlightTime * 1000) {
    setBacklight(false);
  }
}

void Backlight::setBacklight(boolean backlight) {
  if (backlight) {
    digitalWrite(BACKLIGHT_PIN, LOW);
    this->lastUpdate = millis();
    enabled = true;
  } else {
    digitalWrite(BACKLIGHT_PIN, HIGH);
    enabled = false;
  }
}
#endif