#pragma once
#include <unordered_set>

class KeyboardInputData
{

public : 
	KeyboardInputData() = default;

	void SetKeyStatus(char key, bool pressed);
	inline bool IsKeyHeld(const char key) const { return _heldKeys.contains(key); };
private : 
	std::unordered_set<char> _heldKeys{};

};

