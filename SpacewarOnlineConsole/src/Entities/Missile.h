#pragma once
#include <src/Entities/Entity.h>

class Missile : public Entity
{
public:
	Missile();
	
	void Launch(Vector2 velocity, Vector2 spawnPosition);

	void Update(float deltatime, const KeyboardInputData* const inputs) override;
	void Draw(GameWindow& rWindow) override;

private:
	float const _maxVelocity = 4;
};