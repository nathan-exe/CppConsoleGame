#include "Window.h"

Window::Window() {
	_hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwBufferSize = { _SCREEN_WIDTH,_SCREEN_HEIGHT };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, _SCREEN_WIDTH - 1, _SCREEN_HEIGHT - 1 };
}



void Window::Update() {

}

inline bool Window::IsKeyHeld() {

}

#pragma region Display
void Window::BeginFrame()
{
	ReadConsoleOutput(_hOutput, (CHAR_INFO*)_buffer, _dwBufferSize, _dwBufferCoord, &_rcRegion);
}

void Window::SetChar(int x, int y, CHAR_INFO caracterInfo) {
	_buffer[x][y] = caracterInfo;
}

void Window::EndFrame() {
	WriteConsoleOutput(_hOutput, (CHAR_INFO*)_buffer, _dwBufferSize,
		_dwBufferCoord, &_rcRegion);
}
#pragma endregion

