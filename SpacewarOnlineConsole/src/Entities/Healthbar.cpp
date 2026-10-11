#include "Healthbar.h"


Healthbar::Healthbar(int maxHP, bool drawLeftToRight, WORD color)
	: Entity(nullptr) , _hp(maxHP), _maxHP(maxHP), _color(color), _drawLeftToRight(drawLeftToRight)
{
}

void Healthbar::Draw(WindowLibrary::ConsoleWindow& rWindow)
{
	CHAR_INFO character{};
	int x = static_cast<int>(_position.x);
	int y = static_cast<int>(_position.y);
	character.Attributes = _color;
	character.Char.AsciiChar = '|';
	rWindow.SetChar(x, y, character);

	for (int dx = 1; dx <= _maxHP; dx++) {

		character.Char.AsciiChar = (dx <= _hp ? '#' : '-');
		rWindow.SetChar(_drawLeftToRight? x+dx : x-dx, _position.y, character);
	}

	character.Char.AsciiChar = '|';
	rWindow.SetChar(_drawLeftToRight? x + _maxHP + 1 : x-_maxHP - 1, y, character);
}

void Healthbar::Update(UpdateContext ctx)
{
}

void Healthbar::Diminish(char amount)
{
	_hp = max(_hp-amount,0);
}

void Healthbar::Replenish(char amount)
{
	_hp = min(_hp + amount, _maxHP);
}

void Healthbar::FlipGraphics()
{
	_drawLeftToRight = !_drawLeftToRight;
}
