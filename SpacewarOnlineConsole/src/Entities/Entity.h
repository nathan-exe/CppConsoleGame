#pragma once
#include "src/Window/Window.h"
#include "src/Maths/Vector2.h"
#include "src/Enums.h"

class Entity
{
public :
	virtual void Update(float deltatime) = 0;
	virtual void Draw(Window& rWindow) = 0;
	
private :

	inline std::pair<int, int> GetScreenPosition();

	Vector2 _position;
	Vector2 _velocity;
	Heading _heading;
};

