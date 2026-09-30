#pragma once
#include <windows.h> 
#include <set>


class GameWindow
{
private:

	//screen info
	static constexpr SHORT _SCREEN_WIDTH = 10;
	static constexpr SHORT _SCREEN_HEIGHT = 10;
	static constexpr COORD _SCREEN_SIZE{ _SCREEN_WIDTH,_SCREEN_HEIGHT };
	static constexpr COORD _SCREEN_COORD{ 0, 0 };
	SMALL_RECT _screenRegion;

	//screen buffer
	CHAR_INFO _buffer[_SCREEN_WIDTH][_SCREEN_HEIGHT];

	//console handle
	HANDLE _consoleHandle;

	//inputs
	std::set<char> _heldKeys{};

public:
	GameWindow();

	void Update();

	//inputs
	inline bool IsKeyHeld(char key);

	//display
	void BeginFrame();
	void SetChar(int x, int y, CHAR_INFO caracterInfo);
	void EndFrame();
};