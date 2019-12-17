#ifndef _FRONTEND_H
#define _FRONTEND_H

#include "data-source.h"
#include "model.h"

#include <IotWebConf.h>

typedef enum {
  SUCCESS, FAILURE, IN_PROGRESS
} DataSourceStatus;

class Logger {
    public:
    virtual void print(String message);
    virtual void println(String message);
};

class CustomWebConfig {
    public:
    virtual void addParameters(IotWebConf *webConf);
    virtual boolean validate(WebServer *server);
    virtual void displayConfig(Logger *logger);
};

class Frontend {
    public:
    virtual CustomWebConfig* getCustomWebConfig();
    virtual Logger* getLogger();
    virtual void init();
    virtual void connected(Config config, DataSource *dataSource);
    virtual void doLoop();

    virtual void updateDisplayModel(DisplayModel *displayModel);
    virtual void updateDataSourceStatus(DataSourceStatus status);
};

#endif