#include "PerformanceTracking.h"

#ifdef __linux__

#include <fstream>
#include <unistd.h>

float GetMemoryUsageMB() {
	long rss = 0;
	std::ifstream statm("/proc/self/statm");
	if (statm.good()) {
		long pages;
		statm >> pages >> rss;
		statm.close();
	}

	long pageSize = sysconf(_SC_PAGESIZE); //in bytes
	return (rss * pageSize) / (1024.0f * 1024.0f);
}

#endif