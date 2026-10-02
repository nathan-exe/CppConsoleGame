#pragma once
#include <src/Entities/Entity.h>
class Ship;
class Missile : public Entity
{
public:
	Missile();
	
	void Launch(Vector2 velocity, Vector2 spawnPosition);

	void Update(float deltatime, const KeyboardInputData* const inputs) override;
	void Draw(GameWindow& rWindow) override;

private:
	Ship* _pOwner;
	float const _maxVelocity = 50;
};