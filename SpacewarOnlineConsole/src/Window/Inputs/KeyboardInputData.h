#pragma once
#include <set>

class KeyboardInputData
{

public : 
	KeyboardInputData() = default;

	void SetKeyStatus(char key, bool pressed);
	inline bool IsKeyHeld(char key) { return _heldKeys.contains(key); };

private : 
	std::set<char> _heldKeys{};

};

