#include "utility/systemTimer.h"
#include <mach/mach_time.h>


uint64 SystemTimer::GetTickCountSinceInitialization() {
    return mach_absolute_time() / 1000000;
}