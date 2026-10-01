#pragma once
#include <src/Entities/Entity.h>

class Ship : public Entity
{
public : 

	void Update(float deltatime, KeyboardInputData& const inputs) override;
	void Draw(GameWindow& rWindow) override;
};

