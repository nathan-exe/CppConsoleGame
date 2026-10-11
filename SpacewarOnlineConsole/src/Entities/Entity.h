#pragma once
#include "src/Maths/Vector2.h"
#include <map>
#include <vector>

//Include Librairie Statique
#include "ConsoleWindow.h"

class Sprite;


/// <summary>
/// - An abstract class shared by all game objects.
/// - Entities are registered into the game's list of entities upon creation.
/// - They are updated and then drawn each frame if active.
/// - They have a sprite which gets destroyed with them automatically
///   if they were the one who created it.
/// </summary>
class Entity
{
public:
	struct UpdateContext {
		float deltatime;
		const WindowLibrary::ConsoleWindow& rWindow;
		std::map<Entity*, std::vector<Entity*>>& rCollidingEntities;
	};

public :
	Entity(const char* spritePath,WORD color);
	Entity(Sprite* pSprite);
	~Entity();

	virtual void Update(UpdateContext ctx) = 0;
	virtual void Draw(WindowLibrary::ConsoleWindow& rWindow) = 0;
	
	Entity& SetPosition(Vector2 position);
	Entity& SetVelocity(Vector2 velocity);
	Entity& SetCollisionRadius(float newRadius);
	Entity& SetActive(bool activate);

	//getters
	inline bool IsActive() const { return _active; }
	inline Vector2 GetPosition() const { return _position; }
	inline Vector2 GetOldPosition() const { return _position; }
	inline float GetCollisionRadius() const { return _collisionRadius; }

protected : 
	Sprite* _pSprite; 
	Vector2 _position;
	Vector2 _oldPosition; //the position of the object on the previous frame
	Vector2 _velocity;

	float _collisionRadius; //a circle-shaped collider

private:
	bool _active = false;
	bool _ownsSprite; //wether the entity created the sprite or received a pointer to it from outside.

};

