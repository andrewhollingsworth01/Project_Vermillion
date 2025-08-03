#include "PerformanceTracking.h"

#ifdef __APPLE__

#include<mach/mach.h>

float GetMemoryUsageMB() {
	task_basic_info_data_t info;
	mach_msg_type_number_t size = TASK_BASIC_INFO_COUNT;
	task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&info, &size);
	return info.resident_size / (1024.0f * 1024.0f);
}

#endif // __APPLE__
