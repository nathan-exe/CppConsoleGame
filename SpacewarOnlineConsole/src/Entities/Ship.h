#pragma once
#include <src/Entities/Entity.h>

class Ship : public Entity
{
public : 

	void Update(float deltatime, const KeyboardInputData* const inputs) override;
	void Draw(GameWindow& rWindow) override;

private : 
	int const _maxVelocity = 10;
};

