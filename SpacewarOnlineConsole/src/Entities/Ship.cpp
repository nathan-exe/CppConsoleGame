#include "Ship.h"
#include "Missile.h"
#include <vector>
#include <cmath>
#include <string>

Ship::Ship(WORD color)
	: Entity(), _sprite("PlayerShip.txt", color)
{
	SetActive(true);
	_missiles.reserve(20);
	for(int i = 0; i< 20; i++)
		_missiles.emplace_back(this, color);
	//_sprite = Sprite{"truc.txt", FOREGROUND_INTENSITY | FOREGROUND_RED };
}

void Ship::Update(UpdateContext ctx)
{
	static int nextMissile = 0;
	static bool wasHoldingKeyLastFrame = false;

	//read inputs
	Vector2 inputVector;
	const KeyboardInputData* inputs = ctx.rWindow.GetInputs();
	inputVector.x = inputs->IsKeyHeld('d') ? 1 : (inputs->IsKeyHeld('q') ? -1 : 0);
	inputVector.y = inputs->IsKeyHeld('z') ? -1 : (inputs->IsKeyHeld('s') ? 1 : 0);

	//update velocity
	_velocity = _velocity + (inputVector.GetNormalizedVector() * _acceleration * ctx.deltatime);
	_velocity = _velocity.GetMagnitude() > _maxVelocity ? _velocity.WithMagnitude(_maxVelocity) : _velocity;

	//update position
	_position = _position + _velocity * ctx.deltatime;

	//collide with walls
	if (_position.x<0 || _position.x>ctx.rWindow.GetBufferSize().X)
		_velocity.x *= -1;

	if (_position.y<0 || _position.y>ctx.rWindow.GetBufferSize().Y)
		_velocity.y *= -1;

	//Missiles
	if (!wasHoldingKeyLastFrame&&inputs->IsKeyHeld('e')) {
		_missiles[nextMissile++%_missiles.size()].Launch(_velocity, _position);
	}
	wasHoldingKeyLastFrame = inputs->IsKeyHeld('e');


}

void Ship::Draw(GameWindow& rWindow)
{
	//write char to buffer
	_sprite.Draw(rWindow, _position.x, _position.y);
}

std::vector<Missile> Ship::GetMissiles()
{
	return _missiles;
}
