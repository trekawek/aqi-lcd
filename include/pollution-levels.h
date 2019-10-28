#ifndef _POLLUTION_H
#define _POLLUTION_H

#include "model.h"

class PollutionLevels {
    public:
    static const int PM25_LEVELS[];
    static const int PM10_LEVELS[];
    static const int PM25_MAX;
    static const int PM10_MAX;

    static float getLevel(const JsonModel *model);

    private:
    static float findThreshold(float v, const int levels[]);
};

#endif