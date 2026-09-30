#pragma once

#include <windows.h>

class WindowsTimer
{
public : 

	WindowsTimer();

	void Start();

	float GetElapsedSeconds(bool restart);

private :
	LARGE_INTEGER lastUpdateTime;
	LONGLONG freq;
};

