#pragma once
#include <src/Entities/Entity.h>
#include <src/Entities/Missile.h>
#include <src/Graphics/Sprite.h>
#include <vector>

class Ship : public Entity
{
public : 
	Ship(WORD color);
	void Update(UpdateContext ctx) override;
	void Draw(GameWindow& rWindow) override;

	std::vector<Missile> GetMissiles();
private : 
	Sprite _sprite;
	float const _maxVelocity = 20;
	float const _acceleration = 80;

	std::vector<Missile> _missiles;
	//todo : const char _inputScheme[5];//up left down right shoot
};

