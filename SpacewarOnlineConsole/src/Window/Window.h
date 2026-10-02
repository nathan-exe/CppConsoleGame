#pragma once
#include <windows.h> 
#include <set>
#include "Inputs/KeyboardInputData.h"

//120,30 avec maximize avant
//156,41 avec maximize apres


class GameWindow
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
public:
	GameWindow();
	~GameWindow();

	void Update();

	//display
	void BeginFrame();
	void SetChar(int x, int y, CHAR_INFO caracterInfo);
	void Blit(CHAR_INFO* background);
	void EndFrame();

	//getters
	inline const KeyboardInputData* const GetInputs() const { return &_inputs; }
	inline COORD GetBufferSize() const { return _bufferSize; }
};