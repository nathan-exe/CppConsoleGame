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

bool Entity::IsActive()
{
	return _active;
}

void Entity::Activate(bool activate)
{
	_active = activate;
}
