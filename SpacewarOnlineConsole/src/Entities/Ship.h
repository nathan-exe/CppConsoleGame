#pragma once
#include <src/Entities/Entity.h>
#include <src/Entities/Missile.h>
#include <src/Graphics/Sprite.h>
#include <vector>
#include <src/Game/ControlScheme/ControlScheme.h>
#include "Healthbar.h"

class Ship : public Entity
{
public : 
	Ship(WORD color,ControlScheme controlScheme, Vector2 startPosition);

	void Update(UpdateContext ctx) override;
	void Draw(GameWindow& rWindow) override;
	void TakeDamage();

private : 

	float const _maxVelocity = 30;
	float const _acceleration = 120;
	
	int _nextMissileIdInPool = 0;
	bool _wasHoldingShootKeyLastFrame = false;
	Healthbar _healthbar;

	const ControlScheme _controlScheme;

	Sprite _sharedMissileSprite;
	std::vector<Missile> _missilePool;

	
};

