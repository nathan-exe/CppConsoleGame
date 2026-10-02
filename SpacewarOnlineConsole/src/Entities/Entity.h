#pragma once
#include "src/Window/Window.h"
#include "src/Maths/Vector2.h"
#include "src/Enums.h"
#include <list>

class Entity
{
public : 

	struct UpdateContext {
		float deltatime;
		const GameWindow& rWindow;
	};

public :
	Entity();

	virtual void Update(UpdateContext ctx) = 0;
	virtual void Draw(GameWindow& rWindow) = 0;
	
	Entity& SetPosition(Vector2 position);
	Entity& SetVelocity(Vector2 velocity);
	Entity& SetActive(bool activate);

	//getters
	inline bool IsActive() const { return _active; }
	inline Vector2 GetPosition() const { return _position; }
	inline Vector2 GetOldPosition() const { return _position; }
	inline float GetCollisionRadius() const { return _collisionRadius; }

protected : 

	Vector2 _position;
	Vector2 _oldPosition;//the position of the object on the previous frame
	Vector2 _velocity;

	float _collisionRadius;

private:
	bool _active;

};

