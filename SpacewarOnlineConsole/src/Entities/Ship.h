#pragma once
#include <src/Entities/Entity.h>

class Ship : public Entity
{
public : 

	void Update(float deltatime, const KeyboardInputData* const inputs) override;
	void Draw(GameWindow& rWindow) override;

private : 
	CHAR_INFO _sprite;
	float const _maxVelocity = 4;
	float const _acceleration = 10;
};

