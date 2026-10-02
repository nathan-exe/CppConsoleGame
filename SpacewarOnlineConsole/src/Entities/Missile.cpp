#include "Missile.h"

Missile::Missile() : Entity(){}



void Missile::Launch(Vector2 velocity, Vector2 spawnPosition)
{
	this
		->SetPosition(spawnPosition)
		.SetVelocity(velocity.WithMagnitude(_maxVelocity))
		.SetActive(true);
}

void Missile::Update(float deltatime, const KeyboardInputData* const inputs)
{
	_position = _position + _velocity * deltatime;

	//Check that missile doesnt leave the bounds of the game arena
}

void Missile::Draw(GameWindow& rWindow)
{
	CHAR_INFO charinf{};
	charinf.Char.AsciiChar = 'M';
	charinf.Attributes = 0x0E;
	rWindow.SetChar(_position.x, _position.y, charinf);
}
