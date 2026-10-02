#include "Ship.h"
#include "Missile.h"
#include <vector>
#include <cmath>
#include <string>

Ship::Ship()
	: Entity()
{
	SetActive(true);
	_missiles.resize(10);

	_sprite = Sprite{"truc.txt", FOREGROUND_INTENSITY | FOREGROUND_GREEN | BACKGROUND_GREEN };

	//std::string sprite{ "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" };

	//std::vector<CHAR_INFO> vector{};

	//for (char a : sprite) 
	//{
	//	CHAR_INFO charinfo{};
	//	charinfo.Char.AsciiChar = a;
	//	charinfo.Attributes = FOREGROUND_INTENSITY | FOREGROUND_GREEN | BACKGROUND_GREEN;
	//	vector.push_back(charinfo);
	//}

	//_sprite = Sprite{ 9, 9, vector};
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
	//if (inputVector.x != 0 || inputVector.y != 0) {
	//	bool YgreaterThanX = abs(inputVector.y) > abs(inputVector.x);
	//	bool positive = (YgreaterThanX ? inputVector.y : inputVector.x) > 0;
	//	char bitmask = (char)YgreaterThanX | ((char)positive) << 1;
	//	const char sprites[] = "<^>v";
	//	_sprite.Attributes = FOREGROUND_INTENSITY | FOREGROUND_GREEN | BACKGROUND_GREEN;
	//	_sprite.Char.AsciiChar = sprites[bitmask];
	//}
	

}

void Ship::Draw(GameWindow& rWindow)
{
	//write char to buffer
	_sprite.Draw(rWindow, _position.x, _position.y);
	//rWindow.SetChar(static_cast<int>(std::round(_position.x)), static_cast<int>(std::round(_position.y)), _sprite);
}

std::vector<Missile> Ship::GetMissiles()
{
	return _missiles;
}
