#pragma once
#include <windows.h> 



class Window
{
private :
	static constexpr SHORT _SCREEN_WIDTH = 10;
	static constexpr SHORT _SCREEN_HEIGHT = 10;

	CHAR_INFO _buffer[_SCREEN_WIDTH][_SCREEN_HEIGHT];

	HANDLE _hOutput;
	COORD _dwBufferSize;
	COORD _dwBufferCoord;
	SMALL_RECT _rcRegion;

public : 
	Window();

	void Update();

	//inputs
	inline bool IsKeyHeld();

	//display
	void BeginFrame();
	void SetChar(int x, int y, CHAR_INFO caracterInfo);
	void EndFrame();
};

