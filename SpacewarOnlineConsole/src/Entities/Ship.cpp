#include "Ship.h"
#include "Missile.h"
#include <vector>
#include <cmath>
#include <string>
#include "src/Game/Game.h"

constexpr int MAX_HEALTH = 10;

Ship::Ship(WORD color, ControlScheme controlScheme, Vector2 startPosition)
	: Entity("PlayerShip.txt", color),
	_controlScheme(controlScheme),
	_sharedMissileSprite("Missile.txt",color & (~FOREGROUND_INTENSITY)),
	_healthbar(MAX_HEALTH,true,color),
	_missilePool(0),
	_timeSinceLastHit(100)
{
	static int shipID = 0;

	//initialize entity
	this->
		SetPosition(startPosition)
		.SetCollisionRadius(2.5f)
		.SetActive(true);

	//create health bar
	_healthbar
		.SetPosition(shipID == 0 ? Vector2(5, 2) : Vector2(Game::GetSingletonInstance().GetWindow().GetBufferSize().X-5, 2))
		.SetActive(true);
	if (shipID == 1)_healthbar.FlipGraphics();

	//allocate a pool of missiles.
	_missilePool.reserve(20);
	for(int i = 0; i< 20; i++)
		_missilePool.emplace_back(this,&_sharedMissileSprite);

	shipID=(shipID+1)%2;

}

void Ship::Update(UpdateContext ctx)
{
	//read inputs
	Vector2 inputVector;
	const WindowLibrary::KeyboardInputData* inputs = ctx.rWindow.GetInputs();
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
		if(!(_velocity == Vector2())) _missilePool[_nextMissileIdInPool++%_missilePool.size()].Launch(_velocity, _position);
	}
	_wasHoldingShootKeyLastFrame = isKeyHeldNow;

	_timeSinceLastHit += ctx.deltatime;
}

void Ship::Draw(WindowLibrary::ConsoleWindow& rWindow)
{
	const float BLINK_DURATION_AFTER_HIT = .5f;
	if(_timeSinceLastHit> BLINK_DURATION_AFTER_HIT || static_cast<int>(_timeSinceLastHit*20)%2==0) //to blink after taking damage
		_pSprite->Draw(rWindow, _position.x, _position.y);
}

void Ship::TakeDamage(Vector2 knockback, int amount)
{
	_timeSinceLastHit = 0;

	//add impulse
	_velocity = _velocity + knockback;

	//diminish health
	_healthbar.Diminish(amount);
	if (_healthbar.IsEmpty())
		Game::GetSingletonInstance().End();
}

bool Ship::GetIsDestroyed()
{
	return _healthbar.IsEmpty();
}

WORD Ship::GetShipSpriteAttributes()
{
	return _pSprite->GetAttributes();
}
