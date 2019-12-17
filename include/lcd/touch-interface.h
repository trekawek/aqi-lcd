#if FRONTEND_LCD
#ifndef _LCD_TOUCH_INTERFACE_H
#define _LCD_TOUCH_INTERFACE_H

#include <TFT_eSPI.h>

#include "lcd/interface.h"
#include "lcd/backlight.h"

class TouchInterface {
  public:
  TouchInterface(TFT_eSPI *tft, Interface *interface, Backlight *backlight);
  void update();
  
  private:
  TFT_eSPI *tft;
  Interface *interface;
  Backlight *backlight;
  boolean touchDisplayed = false;
  boolean displayTouch = false;
};

#endif
#endif