#pragma once
#include <windows.h> 
#include <set>
#include "Inputs/KeyboardInputData.h"


class GameWindow
{
private:

	//screen info
	static constexpr SHORT _SCREEN_WIDTH = 50;
	static constexpr SHORT _SCREEN_HEIGHT = 50;
	static constexpr COORD _SCREEN_SIZE{ _SCREEN_WIDTH,_SCREEN_HEIGHT };
	static constexpr COORD _SCREEN_COORD{ 0, 0 };
	SMALL_RECT _screenRegion;

	//screen buffer
	CHAR_INFO _buffer[_SCREEN_HEIGHT][_SCREEN_WIDTH];

	//console handle
	HANDLE _consoleOutputHandle;
	HANDLE _consoleInputHandle;

	KeyboardInputData _inputs;

public:
	GameWindow();

	void Update();

	//display
	void BeginFrame();
	void SetChar(int x, int y, CHAR_INFO caracterInfo);
	void EndFrame();

	//getters
	inline const KeyboardInputData* const GetInputs() const { return &_inputs; }

};