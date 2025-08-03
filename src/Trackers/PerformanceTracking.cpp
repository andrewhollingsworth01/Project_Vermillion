#include "PerformanceTracking.h"


#include <fstream>
#include <algorithm>
#include <cstdio>

float currentFrameTime = 0.0f;
float minFrameTime = 1000.0f;
float maxFrameTime = 0.0f;
float totalTime = 0.0f;
int frameCount = 0;

void PerformanceTracking::Update()
{
	currentFrameTime = GetFrameTime() * 1000.0f; // converts to milliseconds

	if (frameTimes.size() >= maxFramesToShow) {
		frameTimes.erase(frameTimes.begin());
	}

	frameTimes.push_back(currentFrameTime);
	minFrameTime = std::min(minFrameTime, currentFrameTime);
	maxFrameTime = std::max(maxFrameTime, currentFrameTime);
	totalTime += currentFrameTime;
	frameCount++;
}

void PerformanceTracking::Draw(int x, int y)
{
	int fps = GetFPS();
	float avg = (frameCount > 0) ? totalTime / frameCount : 0.0f;

	DrawText(TextFormat("FPS: %d", fps), x, y, 20, GREEN);
	DrawText(TextFormat("Frame Time: %.2f ms", currentFrameTime), x, y + 25, 20, YELLOW);
	DrawText(TextFormat("Avg: %.2f ms | Min: %.2f ms | Max: %.2f ms", avg, minFrameTime, maxFrameTime), x, y + 50, 20, ORANGE);

	//float memoryMB = GetMemoryUsageMB();
	//DrawText(TextFormat("Memory: %.2f MB", memoryMB), x, y + 75, 20, SKYBLUE);

	int graphWidth = 200;
	int graphHeight = 60;
	int graphX = x;
	int graphY = y + 110;

	DrawRectangleLines(graphX, graphY, graphWidth, graphHeight, LIGHTGRAY);

	if (frameTimes.size() > 1) {
		for (size_t i = 1; i < frameTimes.size(); i++) {
			float prev = frameTimes[i - 1];
			float curr = frameTimes[i];

			float px = graphX + ((i - 1) * graphWidth / maxFramesToShow);
			float cx = graphX + (i * graphWidth / maxFramesToShow);

			float py = graphY + graphHeight - (prev * graphHeight / 40); // Scale to 40 ms
			float cy = graphY + graphHeight - (curr * graphHeight / 40);

			DrawLine(static_cast<int>(px), static_cast<int>(py), static_cast<int>(cx), static_cast<int>(cy), RED);
		}
	}

	DrawText("Frame Time Graph (MS)", graphX, graphY + graphHeight + 5, 16, GRAY);
}




void PerformanceTracking::LogToFile(const char* filename)
{
	std::ofstream file(filename, std::ios::out);
	if (!file.is_open()) return;

	file << "FrameTime(ms)\\n";

	for (float t : frameTimes) {
		file << t << "\n";
	}

	file << "\nAverage: " << (totalTime / frameCount)
		<< "\nMin: " << minFrameTime
		<< "\nMax: " << maxFrameTime << "\n";

	file.close();
}

float PerformanceTracking::GetFrameTimeMS()
{
	return GetFrameTime() * 10000.0f;
}

