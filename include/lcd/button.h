#if FRONTEND_LCD
#ifndef _BUTTON_H
#define _BUTTON_H

#include "lcd/backlight.h"

class Button {
  public:
  Button(Backlight *backlight);
  void update();

  private:
  Backlight *backlight;
};

#endif
#endif