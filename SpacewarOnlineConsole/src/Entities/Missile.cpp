#include "Missile.h"
#include "Ship.h"

Missile::Missile(const Ship* owner, Sprite* pSprite)
	: Entity(pSprite),
	_pOwner(owner)
{
}


void Missile::Launch(Vector2 velocity, Vector2 spawnPosition)
{
	this
		->SetPosition(spawnPosition)
		.SetVelocity(velocity.WithMagnitude(_maxVelocity))
		.SetCollisionRadius(1.5f)
		.SetActive(true);
}

void Missile::Update(UpdateContext ctx)
{
	//disable self when out of bounds
	if (!ctx.rWindow.ContainsPoint(static_cast<int>(_position.x), static_cast<int>(_position.y)))
		SetActive(false);

	//check for collision
	if(ctx.rCollidingObjects.contains(this))
		for (auto pOther : ctx.rCollidingObjects.at(this)) {
			Ship* otherShip = dynamic_cast<Ship*>(pOther);
			Missile* otherMissile = dynamic_cast<Missile*>(pOther);
			if (otherShip != nullptr && otherShip!=_pOwner) {
				SetActive(false);

				//todo : win
			}
			else if (otherMissile != nullptr) {
				SetActive(false);
			}
		}

	//update position
	_position = _position + _velocity * ctx.deltatime;
}

void Missile::Draw(GameWindow& rWindow)
{
	if (!rWindow.ContainsPoint(static_cast<int>(_position.x), static_cast<int>(_position.y))) {
		return;
	}

	_pSprite->Draw(rWindow, _position.x, _position.y);
}
