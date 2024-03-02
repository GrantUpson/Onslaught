#include "utility/systemTimer.h"
#include <mach/mach_time.h>


uint64 SystemTimer::GetTickCountSinceInitialization() {
    static mach_timebase_info_data_t timebase;

    if (timebase.denom == 0) {
        mach_timebase_info(&timebase);
    }

    return mach_absolute_time() * timebase.numer / timebase.denom;
}