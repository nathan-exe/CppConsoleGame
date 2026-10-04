#pragma once
#include <windows.h> 
#include <set>
#include "Inputs/KeyboardInputData.h"


class ConsoleWindow
{
private: 

	//screen info
	COORD _bufferSize;
	SMALL_RECT _bufferWriteRegion;

	//screen buffer
	CHAR_INFO* _buffer;

	//console handle
	HANDLE _consoleOutputHandle;
	HANDLE _consoleInputHandle;
	HWND _consoleWindowHandle;

	KeyboardInputData _inputs;

	DWORD _startInputMode;
public:
	ConsoleWindow();
	~ConsoleWindow();

	void ResetInputMode();

	void Update();

	//display
	void Clear();
	void Blit(CHAR_INFO* background);
	void SetChar(int x, int y, CHAR_INFO caracterInfo);
	void EndFrame();

	inline bool ContainsPoint(int x, int y) const { return x >= 0 && y >= 0 && x < _bufferSize.X && y < _bufferSize.Y; }


	//getters
	inline const KeyboardInputData* const GetInputs() const { return &_inputs; }
	inline COORD GetBufferSize() const { return _bufferSize; }
};