#if FRONTEND_LCD

#include "lcd/lcd-web-config.h"

LcdWebConfig::LcdWebConfig() {
  this->timezoneOffsetParam = new IotWebConfParameter("Timezone offset (hours)", "timezoneOffset", this->timezoneOffset, 5, "number", NULL, "1", "min=\"-12\" max=\"12\"");
  this->backlightTimeParam = new IotWebConfParameter("Backlight time (seconds)", "backlightTime", this->backlightTime, 5, "number", NULL, "10", "min=\"0\" max=\"60\"");
}

void LcdWebConfig::addParameters(IotWebConf *webConf) {
  webConf->addParameter(this->timezoneOffsetParam);
  webConf->addParameter(this->backlightTimeParam);
}

boolean LcdWebConfig::validate(WebServer *server) {
  boolean valid = true;

  if (server->arg(this->timezoneOffsetParam->getId()).length() == 0) {
    this->timezoneOffsetParam->errorMessage = "Please provide the timezone offset.";
    valid = false;
  }

  if (server->arg(this->backlightTimeParam->getId()).length() == 0) {
    this->backlightTimeParam->errorMessage = "Please provide backlight time or 0 for disable.";
    valid = false;
  }

  return valid;
}

void LcdWebConfig::displayConfig(Logger *logger) {
  logger->print("Timezeone offset: ");
  logger->println(this->timezoneOffset);
  logger->print("Backlight time: ");
  logger->println(this->backlightTime);
}

int LcdWebConfig::getTimezoneOffset() {
  return String(this->timezoneOffset).toInt();
}

int LcdWebConfig::getBacklightTime() {
  return String(this->backlightTime).toInt();
}
#endif