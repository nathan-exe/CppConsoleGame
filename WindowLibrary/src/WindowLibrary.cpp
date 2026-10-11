// WindowLibrary.cpp : Définit les fonctions de la bibliothèque statique.
//

#include "pch.h"
#include "framework.h"
#include "WindowLibrary.h"

void WindowLibrary::KeyboardInputData::SetKeyStatus(char key, bool pressed)
{
    if (pressed)
        _heldKeys.insert(key);
    else
        _heldKeys.erase(key);
}

WindowLibrary::ConsoleWindow::ConsoleWindow()
{
    //retrieve handles to the console
    _consoleOutputHandle = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
    _consoleInputHandle = (HANDLE)GetStdHandle(STD_INPUT_HANDLE);
    _consoleWindowHandle = GetParent(GetConsoleWindow());

    //resize console window
    WINDOWS_THROW_IF_FAILED(
        ShowWindow(_consoleWindowHandle, SW_SHOWMAXIMIZED),
        "couldn't show window.");

    Sleep(50);

    //resize output buffer
    DWORD flags = CONSOLE_FULLSCREEN_MODE;
    WINDOWS_THROW_IF_FAILED(
        SetConsoleDisplayMode(_consoleOutputHandle, flags, &_bufferSize),
        "couldn't set console display mode.");
    _bufferWriteRegion = { 0,0,_bufferSize.X,_bufferSize.Y };
    _buffer = new CHAR_INFO[_bufferSize.X * _bufferSize.Y];

    //enable keyboard inputs

    WINDOWS_THROW_IF_FAILED(
        GetConsoleMode(_consoleInputHandle, &_startInputMode),
        "couldn't get console mode."
    );

    WINDOWS_THROW_IF_FAILED(
        SetConsoleMode(_consoleInputHandle, ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT),
        "Couldn't set console mode.");
}

WindowLibrary::ConsoleWindow::~ConsoleWindow()
{
    delete[] _buffer;
}

void WindowLibrary::ConsoleWindow::ResetInputMode()
{

    WINDOWS_THROW_IF_FAILED(
        SetConsoleMode(_consoleInputHandle, _startInputMode),
        "Couldn't set console mode.");
}

void WindowLibrary::ConsoleWindow::Update() {

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
            auto key = inputBuffer[i].Event.KeyEvent;
            _inputs.SetKeyStatus(key.uChar.AsciiChar, key.bKeyDown);
        }
    }
}

#pragma region Display
void WindowLibrary::ConsoleWindow::Clear()
{
    //clear buffer
    memset(_buffer, 0, _bufferSize.Y * _bufferSize.X * sizeof(CHAR_INFO));
}

void WindowLibrary::ConsoleWindow::SetChar(int x, int y, CHAR_INFO caracterInfo) {

#ifdef _DEBUG
    if (!ContainsPoint(x, y))
        throw std::out_of_range("Can't write characters outside of the window's rect.");
#endif 


    * (_buffer + y * _bufferSize.X + x) = caracterInfo;
}

void WindowLibrary::ConsoleWindow::Blit(CHAR_INFO* background)
{
    memcpy(_buffer, background, _bufferSize.Y * _bufferSize.X * sizeof(CHAR_INFO));
}

void WindowLibrary::ConsoleWindow::EndFrame() {
    //write buffered data into the console
    WriteConsoleOutput(_consoleOutputHandle, (CHAR_INFO*)_buffer, _bufferSize,
        { 0,0 }, &_bufferWriteRegion);
}
#pragma endregion
