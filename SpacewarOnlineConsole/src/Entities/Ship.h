#pragma once
#include <src/Entities/Entity.h>
#include <src/Entities/Missile.h>
#include <vector>

class Ship : public Entity
{
public : 
	Ship();
	void Update(float deltatime, const KeyboardInputData* const inputs) override;
	void Draw(GameWindow& rWindow) override;

	std::vector<Missile> GetMissiles();
private : 
	CHAR_INFO _sprite;
	float const _maxVelocity = 10;
	float const _acceleration = 20;

	std::vector<Missile> _missiles;
};

