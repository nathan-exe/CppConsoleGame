#include "Window.h"
#include <array>
#include <vector>

GameWindow::GameWindow()  : 
	_screenRegion( 0, 0, _SCREEN_WIDTH - 1, _SCREEN_HEIGHT - 1 )
{
	//retrieve a handle to the console
	_consoleHandle = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	
	//enable keyboard inputs
    SetConsoleMode(_consoleHandle, ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT);
}



void GameWindow::Update() {
    //fetch number of input events
    DWORD inputBufferSize = 0;
    GetNumberOfConsoleInputEvents(_consoleHandle, &inputBufferSize);
    if (inputBufferSize == 0)
        return; // avoids blocking on empty input buffers

    //allocate input buffer
    std::vector<INPUT_RECORD> inputBuffer(inputBufferSize);
    
    //Read input buffer
    DWORD inputReadsCount;
    if (!ReadConsoleInput(
        _consoleHandle,      // input buffer handle
        inputBuffer.data(),     // buffer to read into
        inputBufferSize,         // size of read buffer
        &inputReadsCount)) // number of records read
    {
        //todo : throw
    }

    for (int i = 0; i < inputReadsCount; i++)
    {
        if (inputBuffer[i].EventType == KEY_EVENT) {
            auto key = inputBuffer[inputReadsCount - 1].Event.KeyEvent;
            //process input
            //printf("Key event: \"%c\" ", key.uChar.AsciiChar);

            if (key.bKeyDown)
                printf("key pressed\n" + key.uChar.AsciiChar);
            else printf("key released\n");
        }
    }
    
}

inline bool GameWindow::IsKeyHeld() {
    return false;
}

#pragma region Display
void GameWindow::BeginFrame()
{
	ReadConsoleOutput(_consoleHandle, (CHAR_INFO*)_buffer, _SCREEN_SIZE, _SCREEN_COORD, &_screenRegion);
}

void GameWindow::SetChar(int x, int y, CHAR_INFO caracterInfo) {
	_buffer[x][y] = caracterInfo;
}

void GameWindow::EndFrame() {
	WriteConsoleOutput(_consoleHandle, (CHAR_INFO*)_buffer, _SCREEN_SIZE,
        _SCREEN_COORD, &_screenRegion);
}
#pragma endregion

