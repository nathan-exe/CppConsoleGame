#include "Window.h"
#include <array>
#include <vector>
#include <src/Macros.h>
#include <iostream>

GameWindow::GameWindow()  : 
	_screenRegion( 0, 0, _SCREEN_WIDTH - 1, _SCREEN_HEIGHT - 1 )
{
	//retrieve handles to the console
	_consoleOutputHandle = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	_consoleInputHandle = (HANDLE)GetStdHandle(STD_INPUT_HANDLE);

    
	
	//enable keyboard inputs
    WINDOWS_THROW_IF_FAILED(
        SetConsoleMode(_consoleInputHandle, ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT),
        "Couldn't set console mode.");
}

void GameWindow::Update() {

    //fetch number of input events
    DWORD inputBufferSize = 0;
    WINDOWS_THROW_IF_FAILED(
        GetNumberOfConsoleInputEvents(_consoleInputHandle, &inputBufferSize),
        "couldn't get number of console events.");

    if (inputBufferSize == 0)
        return; // avoid blocking on empty input buffers

    //allocate input buffer
    std::vector<INPUT_RECORD> inputBuffer(inputBufferSize);
    
    //fetch console inputs into input buffer
    DWORD inputReadsCount;
    WINDOWS_THROW_IF_FAILED(
        ReadConsoleInput(_consoleInputHandle, inputBuffer.data(), inputBufferSize, &inputReadsCount)
        , "couldn't read console input.");

    //foreach input event
    for (int i = 0; i < inputReadsCount; i++)
    {
        //process key event
        if (inputBuffer[i].EventType == KEY_EVENT) {
            auto key = inputBuffer[inputReadsCount - 1].Event.KeyEvent;
            _inputs.SetKeyStatus(key.uChar.AsciiChar, key.bKeyDown);
        }
    }
}

#pragma region Display
void GameWindow::BeginFrame()
{
	//ReadConsoleOutput(_consoleOutputHandle, (CHAR_INFO*)_buffer, _SCREEN_SIZE, _SCREEN_COORD, &_screenRegion);
    
    //todo : clear buffer ???
    for (int y = 0; y < _SCREEN_HEIGHT; y++) {
        for (int x = 0; x < _SCREEN_WIDTH; x++) {
            CHAR_INFO charinf{};
            charinf.Char.AsciiChar = x==5 ? '#' : '.';
            charinf.Char.AsciiChar = y==5 ? '|' : charinf.Char.AsciiChar;
            charinf.Attributes = 0x0E;
            SetChar(x, y, charinf);
        }
    }
}

void GameWindow::SetChar(int x, int y, CHAR_INFO caracterInfo) {
	_buffer[y][x] = caracterInfo;
}

void GameWindow::EndFrame() {
	WriteConsoleOutput(_consoleOutputHandle, (CHAR_INFO*)_buffer, _SCREEN_SIZE,
        _SCREEN_COORD, &_screenRegion);
}
#pragma endregion

