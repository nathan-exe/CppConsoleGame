#pragma once
#include <src/Entities/Entity.h>
class Ship;
class Missile : public Entity
{
public:
	Missile();
	
	void Launch(Vector2 velocity, Vector2 spawnPosition);

	void Update(UpdateContext ctx) override;
	void Draw(GameWindow& rWindow) override;

private:
	Sprite _sprite;
	Ship* _pOwner;
	const float _maxVelocity = 50;
};