#pragma once
#include "src/Window/Window.h"
#include "src/Maths/Vector2.h"
#include "src/Enums.h"

class Entity
{
public :
	Entity();

	virtual void Update(float deltatime,const KeyboardInputData* const inputs) = 0;
	virtual void Draw(GameWindow& rWindow) = 0;
	
	Entity& SetPosition(Vector2 position);
	Entity& SetVelocity(Vector2 velocity);
	void Activate(bool activate);


	bool IsActive();
private :
	bool _active;
	
protected : 
	Vector2 _position;
	Vector2 _velocity;
	Heading _heading;

	inline std::pair<int, int> GetScreenPosition() {};
};

