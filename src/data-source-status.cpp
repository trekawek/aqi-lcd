#include "data-source-status.h"

DataSourceStatus::DataSourceStatus(TFT_eSPI *tft) {
    this->tft = tft;
}

void DataSourceStatus::update(DataSourceStatusType status) {
  uint32_t color;
  switch (status) {
    case SUCCESS:
    color = TFT_GREEN;
    break;

    case FAILURE:
    color = TFT_RED;
    break;

    case IN_PROGRESS:
    color = TFT_YELLOW;
    break;
 }
 tft->fillCircle(30, 10, 3, color);
}
