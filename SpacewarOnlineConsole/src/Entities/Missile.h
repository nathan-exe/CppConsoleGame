#pragma once
#include <src/Entities/Entity.h>
class Ship;
class Missile : public Entity
{
public:
	Missile(const Ship* owner,Sprite* pSprite);
	void Launch(Vector2 velocity, Vector2 spawnPosition);

	void Update(UpdateContext ctx) override;
	void Draw(GameWindow& rWindow) override;
private:
	const Ship* _pOwner;
	const float _maxVelocity = 100;
};