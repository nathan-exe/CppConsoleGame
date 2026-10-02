#include "Entity.h"
#include <src/Game/Game.h>

Entity::Entity(const char* spritePath, WORD color)
	: _pSprite(new Sprite(spritePath,color)), _ownsSprite(true)
{
	Game::GetInstance().RegisterEntity(this);
}

Entity::Entity(Sprite* pSprite)
	: _pSprite(pSprite), _ownsSprite(false)
{
	Game::GetInstance().RegisterEntity(this);
}

Entity::~Entity()
{
	if (_ownsSprite)
		delete _pSprite;
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
