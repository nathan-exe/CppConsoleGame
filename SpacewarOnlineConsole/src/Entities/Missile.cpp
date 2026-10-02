#include "Missile.h"

Missile::Missile() : Entity(){}



void Missile::Launch(Vector2 velocity, Vector2 spawnPosition)
{
	this
		->SetPosition(spawnPosition)
		.SetVelocity(velocity.WithMagnitude(_maxVelocity))
		.SetActive(true);
}

void Missile::Update(UpdateContext ctx)
{
	if (_position.x < 0 || _position.x >= ctx.rWindow.GetBufferSize().X
		|| _position.y < 0 || _position.y >= ctx.rWindow.GetBufferSize().Y)
		SetActive(false);

	_position = _position + _velocity * ctx.deltatime;
	//Check that missile doesnt leave the bounds of the game arena
}

void Missile::Draw(GameWindow& rWindow)
{
	if (_position.x < 0 || _position.x >= rWindow.GetBufferSize().X
		|| _position.y < 0 || _position.y >= rWindow.GetBufferSize().Y) {
		return;
	}

	CHAR_INFO charinf{};
	charinf.Char.AsciiChar = 'M';
	charinf.Attributes = 0x0E;
	rWindow.SetChar(_position.x, _position.y, charinf);
}
