#pragma once
#include "src/Entities/Entity.h"
class Ship;

/// <summary>
/// Missiles are shot by battle ships and advance in a straight line until 
/// they go outside of the screen or collide with another ship or missile.
/// </summary>
class Missile : public Entity
{
public:
	Missile();
	Missile(const Ship* owner,Sprite* pSprite);
	void Launch(Vector2 velocity, Vector2 spawnPosition);

	void Update(UpdateContext ctx) override;
	void Draw(ConsoleWindow& rWindow) override;
private:
	const Ship* _pOwner = nullptr;
	const float _maxVelocity = 100;
};