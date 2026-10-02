#include "Ship.h"
#include "Missile.h"
#include <vector>
#include <cmath>

Ship::Ship()
	: Entity()
{
	SetActive(true);
	_missiles.resize(10);
}

void Ship::Update(float deltatime, const KeyboardInputData* const inputs)
{
	

	//read inputs
	Vector2 inputVector;
	inputVector.x = inputs->IsKeyHeld('d') ? 1 : (inputs->IsKeyHeld('q') ? -1 : 0);
	inputVector.y = inputs->IsKeyHeld('z') ? -1 : (inputs->IsKeyHeld('s') ? 1 : 0);

	//update velocity
	_velocity = _velocity + (inputVector.GetNormalizedVector() * _acceleration * deltatime);
	_velocity = _velocity.GetMagnitude() > _maxVelocity ? _velocity.WithMagnitude(_maxVelocity) : _velocity;

	//update position
	_position = _position + _velocity * deltatime;

	//Missiles
	if (inputs->IsKeyHeld('e')) {
		_missiles[0].Launch(_velocity,_position);
	}

	//update sprite
	if (inputVector.x != 0 || inputVector.y != 0) {
		bool YgreaterThanX = abs(inputVector.y) > abs(inputVector.x);
		bool positive = (YgreaterThanX ? inputVector.y : inputVector.x) > 0;
		char bitmask = (char)YgreaterThanX | ((char)positive) << 1;
		const char sprites[] = "<^>v";
		_sprite.Attributes = FOREGROUND_INTENSITY | FOREGROUND_GREEN | BACKGROUND_GREEN;
		_sprite.Char.AsciiChar = sprites[bitmask];
	}

	//check for collisions

	

}

void Ship::Draw(GameWindow& rWindow)
{
	//write char to buffer
	rWindow.SetChar(static_cast<int>(std::round(_position.x)), static_cast<int>(std::round(_position.y)), _sprite);
}

std::vector<Missile> Ship::GetMissiles()
{
	return _missiles;
}
