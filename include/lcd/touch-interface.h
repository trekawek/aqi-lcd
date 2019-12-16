#if FRONTEND_LCD
#ifndef _LCD_TOUCH_INTERFACE_H
#define _LCD_TOUCH_INTERFACE_H

#include <TFT_eSPI.h>

#include "lcd/interface.h"

class TouchInterface {
  public:
  TouchInterface(TFT_eSPI *tft, Interface *interface, unsigned long backlightTime);
  void update();
  void setBacklight(boolean backlight);
  
  private:
  TFT_eSPI *tft;
  Interface *interface;
  boolean touchDisplayed = false;
  boolean displayTouch = false;
  unsigned long lastUpdate = -60 * 1000;
  unsigned long backlightTime = 10 * 1000;
};

#endif
#endif