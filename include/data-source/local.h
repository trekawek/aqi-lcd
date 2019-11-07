#ifndef _LOCAL_DATA_SOURCE_H
#define _LOCAL_DATA_SOURCE_H

#include <Arduino.h>
#include "model.h"
#include "data-source.h"

class LocalDataSource : public DataSource {
    public:
    LocalDataSource(String url);
    boolean readModel(JsonModel *model);

    private:
    static const String P10_VALUES[];
    static const String P25_VALUES[];
    static const String TEMP_VALUES[];
    static const String HUMIDITY_VALUES[];
    static const String PRESSURE_VALUES[];

    static boolean inArray(const String array[], String str);
};

#endif