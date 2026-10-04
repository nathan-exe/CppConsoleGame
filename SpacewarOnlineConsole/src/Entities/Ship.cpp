#include "Ship.h"
#include "Missile.h"
#include <vector>
#include <cmath>
#include <string>

constexpr int MAX_HEALTH = 10;

Ship::Ship(WORD color, ControlScheme controlScheme, Vector2 startPosition)
	: Entity("PlayerShip.txt", color),
	_controlScheme(controlScheme),
	_sharedMissileSprite("Missile.txt",color & (~FOREGROUND_INTENSITY)),
	_healthbar(MAX_HEALTH,true,color)
{
	static int shipID = 0;

	this->
		SetPosition(startPosition)
		.SetCollisionRadius(2.5f)
		.SetActive(true);

	_healthbar
		.SetPosition(shipID == 0 ? Vector2(5, 5) : Vector2(Game::GetInstance().GetWindow().GetBufferSize().X-5, 5))
		.SetActive(true);
	if (shipID % 2 == 1)_healthbar.FlipGraphics();

	//allocate a pool of missiles.
	_missilePool.reserve(20);
	for(int i = 0; i< 20; i++)
		_missilePool.emplace_back(this,&_sharedMissileSprite);

	shipID++;

}

void Ship::Update(UpdateContext ctx)
{
	//read inputs
	Vector2 inputVector;
	const KeyboardInputData* inputs = ctx.rWindow.GetInputs();
	inputVector.x = inputs->IsKeyHeld(_controlScheme.key_right) ? 1 : (inputs->IsKeyHeld(_controlScheme.key_left) ? -1 : 0);
	inputVector.y = inputs->IsKeyHeld(_controlScheme.key_up) ? -1 : (inputs->IsKeyHeld(_controlScheme.key_down) ? 1 : 0);

	//update velocity
	_velocity = _velocity + (inputVector.GetNormalizedVector() * _acceleration * ctx.deltatime);
	_velocity = _velocity.GetMagnitude() > _maxVelocity ? _velocity.WithMagnitude(_maxVelocity) : _velocity;

	//update position
	_position = _position + _velocity * ctx.deltatime;

	//bounce if touching screen bounds
	if (_position.x<0 || _position.x>ctx.rWindow.GetBufferSize().X)
		_velocity.x *= -1;

	if (_position.y<0 || _position.y>ctx.rWindow.GetBufferSize().Y)
		_velocity.y *= -1;

	//shoot a missile on shoot key pressed
	bool isKeyHeldNow = inputs->IsKeyHeld(_controlScheme.key_shoot);
	if (!_wasHoldingShootKeyLastFrame && isKeyHeldNow) {
		_missilePool[_nextMissileIdInPool++%_missilePool.size()].Launch(_velocity, _position);
	}
	_wasHoldingShootKeyLastFrame = isKeyHeldNow;
}

void Ship::Draw(GameWindow& rWindow)
{
	_pSprite->Draw(rWindow, _position.x, _position.y);
}

void Ship::TakeDamage()
{
	_healthbar.Diminish(1);
}