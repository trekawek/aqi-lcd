#ifndef _FRONTEND_H
#define _FRONTEND_H

#include "data-source.h"
#include "model.h"

typedef enum {
  SUCCESS, FAILURE, IN_PROGRESS
} DataSourceStatus;

class Frontend {
    public:
    virtual void init();
    virtual void connected(Config config, DataSource *dataSource);
    virtual void doLoop();

    virtual void updateDisplayModel(DisplayModel *displayModel);
    virtual void updateDataSourceStatus(DataSourceStatus status);
    virtual void print(String message);
    virtual void println(String message);
};

#endif