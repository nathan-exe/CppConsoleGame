#include "WindowsTimer.h"

WindowsTimer::WindowsTimer() 
{
	QueryPerformanceCounter(&lastUpdateTime);
	LARGE_INTEGER li_freq;
	QueryPerformanceFrequency(&li_freq);
	freq = li_freq.QuadPart;
	freq /= 1000;
}

void WindowsTimer::Start()
{
	QueryPerformanceCounter(&lastUpdateTime);
}

float WindowsTimer::GetElapsedSeconds(bool restart = false)
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	LONGLONG elapsedLong = currentTime.QuadPart - lastUpdateTime.QuadPart;

	float elapsed = (float)((float)elapsedLong / (float)freq);
	elapsed /= 1000.0f;

	if (restart) lastUpdateTime = currentTime;

	return elapsed;
}
