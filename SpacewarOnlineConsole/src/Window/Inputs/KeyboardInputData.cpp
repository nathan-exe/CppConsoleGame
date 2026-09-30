#include "KeyboardInputData.h"

void KeyboardInputData::SetKeyStatus(char key, bool pressed)
{
    if (pressed)
        _heldKeys.insert(key);
    else
        _heldKeys.erase(key);
}
