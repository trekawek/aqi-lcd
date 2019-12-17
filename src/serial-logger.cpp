#include "serial-logger.h"

void SerialLogger::print(String message) {
  Serial.print(message);
}

void SerialLogger::println(String message) {
  Serial.println(message);
}
