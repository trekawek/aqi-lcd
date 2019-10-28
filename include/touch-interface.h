#ifndef _TOUCH_INTERFACE_H
#define _TOUCH_INTERFACE_H

#include <TFT_eSPI.h>

#include "interface.h"

class TouchInterface {
  public:
  TouchInterface(TFT_eSPI *tft, Interface *interface);
  void update();
  
  private:
  TFT_eSPI *tft;
  Interface *interface;
};

#endif