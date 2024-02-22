#include "utility/systemTimer.h"
#include "windows.h"


uint64 SystemTimer::GetTickCountSinceInitialization() {
    return GetTickCount();
}