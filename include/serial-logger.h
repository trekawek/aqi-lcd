#ifndef _SERIAL_LOGGER_H
#define _SERIAL_LOGGER_H

#include "frontend.h"

#include <Arduino.h>

class SerialLogger : public Logger {
    public:
    void print(String message);
    void println(String message);
};

#endif