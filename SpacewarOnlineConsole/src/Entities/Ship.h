#pragma once
#include <src/Entities/Entity.h>
#include <src/Entities/Missile.h>
#include <src/Graphics/Sprite.h>
#include <vector>
#include <src/Game/ControlScheme/ControlScheme.h>

class Ship : public Entity
{
public : 
	Ship(WORD color,ControlScheme controlScheme, Vector2 startPosition);
	void Update(UpdateContext ctx) override;
	void Draw(GameWindow& rWindow) override;

	std::vector<Missile> GetMissiles();
private : 

	float const _maxVelocity = 20;
	float const _acceleration = 80;
	
	int _nextMissileIdInPool = 0;
	bool _wasHoldingShootKeyLastFrame = false;
	
	Sprite _sprite;
	const ControlScheme _controlScheme;
	std::vector<Missile> _missilePool;

	
};

