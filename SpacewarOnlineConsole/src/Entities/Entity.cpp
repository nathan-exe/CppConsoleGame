#include "Entity.h"
#include <src/Game/Game.h>

Entity::Entity()
{
	Game::GetInstance().RegisterEntity(this);
	_active = false;
}

Entity& Entity::SetPosition(Vector2 position)
{
	_position = position;
	return *this;
}

Entity& Entity::SetVelocity(Vector2 velocity)
{
	_velocity = velocity;
	return *this;
}

Entity& Entity::SetActive(bool activate)
{
	_active = activate;
	return *this;
}
