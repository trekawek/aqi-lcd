#if FRONTEND_LCD
#ifndef _LCD_BACKLIGHT_H
#define _LCD_BACKLIGHT_H

#include <TFT_eSPI.h>
#include <limits.h>

class Backlight {
  public:
  Backlight();
  void begin();
  void update();
  void setTimeout(unsigned long backlightTime);
  void setBacklight(boolean backlight);

  private:
  unsigned long lastUpdate = -60 * 1000;
  unsigned long backlightTime = 0;
  bool enabled = false;
};

#endif
#endif