#if FRONTEND_LCD
#ifndef _LCD_LOGGER_H
#define _LCD_LOGGER_H

#include "frontend.h"

#include <TFT_eSPI.h>

class LcdLogger : public Logger {
    public:
    LcdLogger(TFT_eSPI *tft);
    void print(String message);
    void println(String message);

    private:
    TFT_eSPI *tft;
};

#endif
#endif