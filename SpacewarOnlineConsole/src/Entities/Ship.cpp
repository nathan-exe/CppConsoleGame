#include "Ship.h"

void Ship::Update(float deltatime, const KeyboardInputData* const inputs)
{

}

void Ship::Draw(GameWindow& rWindow)
{
	CHAR_INFO charinf{};
	charinf.Char.AsciiChar = 'A';
	charinf.Attributes = 0x0E;
	rWindow.SetChar(20, 20, charinf);
}
