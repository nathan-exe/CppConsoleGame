#pragma once
#include <src/Entities/Entity.h>
#include <src/Graphics/Sprite.h>
#include <vector>
#include "src/Game/ControlScheme/ControlScheme.h"
#include "Healthbar.h"
#include "src/Entities/Missile.h"


/// <summary>
/// A battle ship controled byb players through keyboard inputs.
/// it can shoot missiles is destroyable by other ships's missiles.
/// </summary>
class Ship : public Entity
{
public : 
	Ship(WORD color,ControlScheme controlScheme, Vector2 startPosition);

	void Update(UpdateContext ctx) override;
	void Draw(WindowLibrary::ConsoleWindow& rWindow) override;
	void TakeDamage(Vector2 knockback, int amount);

private : 

	float const _maxVelocity = 30;
	float const _acceleration = 120;
	
	int _nextMissileIdInPool = 0;
	bool _wasHoldingShootKeyLastFrame = false;

	float _timeSinceLastHit = 100;

	const ControlScheme _controlScheme;
	Healthbar _healthbar;
	Sprite _sharedMissileSprite;
	std::vector<Missile> _missilePool;

	
};

