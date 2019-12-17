#if FRONTEND_LCD
#ifndef _LCD_BACKLIGHT_H
#define _LCD_BACKLIGHT_H

#include <TFT_eSPI.h>

class Backlight {
  public:
  Backlight(unsigned long backlightTime);
  void update();
  void setBacklight(boolean backlight);

  private:
  unsigned long lastUpdate = -60 * 1000;
  unsigned long backlightTime = 10 * 1000;
};

#endif
#endif