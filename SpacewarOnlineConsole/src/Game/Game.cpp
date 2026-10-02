#include "Game.h"
#include "src/Maths/Vector2.h"
#include <wincontypes.h>
#include <src/Entities/Ship.h>
#include <src/Entities/Entity.h>
#include <src/Window/Window.h>
#include <src/Maths/WindowsTimer.h>
#include <map>

Game* Game::instance = nullptr;

Game::Game() {
	instance = this;
}

void Game::Run()
{
	Ship shipp{};

	WindowsTimer timer{};
	timer.Start();

	while (true) {
		float timePassed = timer.GetElapsedSeconds(true);
		
		//=== update game logic ===
		
		_window.Update();

		//collision detection
		std::map<Entity*,std::vector<Entity*>> collidingEntities;
		for (int i = 0; i < _entities.size(); i++)
		{
			for(int j = 0;j < _entities.size() - (i+1); j++)
			{
				const Entity& entityA = *_entities[i];
				const Entity& entityB = *_entities[j];
				
				//capsule intersection for continuous collision detection between fast moving objects
				const float distanceBetweenSegments = Vector2::GetDistanceBetweenSegments(
					{ entityA.GetPosition(),entityA.GetOldPosition() },
					{ entityB.GetPosition(),entityB.GetOldPosition() }
				);
				const bool capsulesIntersectEachother = distanceBetweenSegments <= entityA.GetCollisionRadius() + entityB.GetCollisionRadius();
			
				if (capsulesIntersectEachother) {
					collidingEntities[_entities[i]].push_back(_entities[j]);
					collidingEntities[_entities[j]].push_back(_entities[i]);
				}
			}
		}

		for (auto pEntity : _entities) {
			if(pEntity->IsActive())
				pEntity->Update(timePassed, _window.GetInputs());
		}

		//=== draw game ===

		_window.BeginFrame();
		for (auto& rEntity : _entities) {
			if (rEntity->IsActive()) rEntity->Draw(_window);
		}
		_window.EndFrame();

		//todo : end deltatime timer and retrieve value
	}
}

void Game::RegisterEntity(Entity* entity) {
	_entities.push_back(entity);
}

void Game::UnregisterEntity(Entity* entity) {
	for (auto i = _entities.begin(); i != _entities.end();) {
		if (*i == entity)
			i = _entities.erase(i);
		else
			i++;
	}
}
