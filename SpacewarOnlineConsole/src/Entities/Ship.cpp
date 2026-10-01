#include "Ship.h"
#include "Missile.h"

void Ship::Update(float deltatime, const KeyboardInputData* const inputs)
{
	Vector2 inputVector;

	inputVector.x = inputs->IsKeyHeld('d') ? 1 : (inputs->IsKeyHeld('q') ? -1 : 0);
	inputVector.y = inputs->IsKeyHeld('z') ? -1 : (inputs->IsKeyHeld('s') ? 1 : 0);

	//Position
	_velocity = _velocity + (inputVector.GetNormalizedVector() * _acceleration * deltatime);

	_velocity = _velocity.GetMagnitude() > _maxVelocity ? _velocity.WithMagnitude(_maxVelocity) : _velocity;

	_position = _position + _velocity * deltatime;

	////Missiles
	//if (inputs->IsKeyHeld('e')) {
	//	Missile missile{_velocity};
	//}

}

void Ship::Draw(GameWindow& rWindow)
{
	CHAR_INFO charinf{};
	charinf.Char.AsciiChar = 'A';
	charinf.Attributes = 0x0E;
	rWindow.SetChar(_position.x, _position.y, charinf);
}
