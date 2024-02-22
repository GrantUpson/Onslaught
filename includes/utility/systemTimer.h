#ifndef SYSTEMTIMER_H
#define SYSTEMTIMER_H

#include "types.h"


class SystemTimer {
public:
    SystemTimer() = default;
    ~SystemTimer() = default;

    static uint64 GetTickCountSinceInitialization();
};


#endif