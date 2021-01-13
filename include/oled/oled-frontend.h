#if FRONTEND_OLED
#ifndef _OLED_FRONTEND_H
#define _OLED_FRONTEND_H

#include "data-source.h"
#include "frontend.h"
#include "oled/oled-web-config.h"

class OledFrontend : public Frontend {
    public:
    OledFrontend();

    CustomWebConfig* getCustomWebConfig();
    Logger* getLogger();

    void init();
    void connected(Config config, DataSource *dataSource);
    void doLoop();

    void updateDisplayModel(DisplayModel *displayModel);
    void updateDataSourceStatus(DataSourceStatus status);

    private:
    Logger *logger;
    OledWebConfig *oledWebConfig;
};

#endif
#endif