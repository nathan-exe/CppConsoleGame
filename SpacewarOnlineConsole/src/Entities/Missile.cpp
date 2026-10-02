#include "Missile.h"

Missile::Missile(const Ship* owner, WORD color) : Entity(),
	_sprite("Missile.txt",color), _pOwner(owner)
{
}

void Missile::Launch(Vector2 velocity, Vector2 spawnPosition)
{
	this
		->SetPosition(spawnPosition)
		.SetVelocity(velocity.WithMagnitude(_maxVelocity))
		.SetActive(true);
}

void Missile::Update(UpdateContext ctx)
{
	if (!ctx.rWindow.ContainsPoint(static_cast<int>(_position.x), static_cast<int>(_position.y)))
		SetActive(false);

	_position = _position + _velocity * ctx.deltatime;
	//Check that missile doesnt leave the bounds of the game arena
}

void Missile::Draw(GameWindow& rWindow)
{
	if (!rWindow.ContainsPoint(static_cast<int>(_position.x), static_cast<int>(_position.y))) {
		return;
	}

	_sprite.Draw(rWindow, _position.x, _position.y);
}
