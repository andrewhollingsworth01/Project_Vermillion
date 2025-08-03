#include "PerformanceTracking.h"

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define NOGDI
#include <Windows.h>
#include <Psapi.h>

float GetMemoryUsageMB() {
	PROCESS_MEMORY_COUNTERS memInfo;
	if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
		return memInfo.WorkingSetSize / (1024.0f * 1024.0f);
	}
	return 0.0f;
}

#endif // _WIN32
