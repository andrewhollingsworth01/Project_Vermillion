#pragma once

#include <vector>

#include "raylib.h"

class PerformanceTracking
{
public:
	void Update();
	void Draw(int x, int y);
	void LogToFile(const char* filename);
	// float GetMemoryUsageMB();

private:
	std::vector<float> frameTimes;
	static const int maxFramesToShow = 100;

	float currentFrameTime;
	float minFrameTime;
	float maxFrameTime;
	float totalTime;
	int frameCount;

	
	float GetFrameTimeMS();
};