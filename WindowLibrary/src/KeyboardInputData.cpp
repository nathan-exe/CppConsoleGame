#include "pch.h"
#include "KeyboardInputData.h"

void WindowLibrary::KeyboardInputData::SetKeyStatus(char key, bool pressed)
{
    if (pressed)
        _heldKeys.insert(key);
    else
        _heldKeys.erase(key);
}
