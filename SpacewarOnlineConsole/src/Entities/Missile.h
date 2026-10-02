#pragma once
#include <src/Entities/Entity.h>
class Ship;
class Missile : public Entity
{
public:
	Missile(const Ship* owner,WORD color);
	
	void Launch(Vector2 velocity, Vector2 spawnPosition);

	void Update(UpdateContext ctx) override;
	void Draw(GameWindow& rWindow) override;
private:
	Sprite _sprite;
	const Ship* _pOwner;
	const float _maxVelocity = 50;
};