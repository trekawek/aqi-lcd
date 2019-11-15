#ifndef _DATA_SOURCE_STATUS_H
#define _DATA_SOURCE_STATUS_H

#include <Arduino.h>
#include <TFT_eSPI.h>

typedef enum {
  SUCCESS, FAILURE, IN_PROGRESS
} DataSourceStatusType;

class DataSourceStatus {
    public:
    DataSourceStatus(TFT_eSPI *tft);
    void update(DataSourceStatusType status);

    private:
    TFT_eSPI *tft;
};

#endif