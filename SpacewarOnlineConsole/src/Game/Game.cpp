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
	_gameHasEnded = false;
}

bool Game::Run()
{
	// === Game Initialisation ===

	//load sprites
	Sprite _backgroundSprite{ "background.txt", FOREGROUND_BLUE };

	Ship player1(FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN, ControlScheme('z', 'q', 's', 'd', 'c'), Vector2(10, _window.GetBufferSize().Y / 2));
	Ship player2(FOREGROUND_INTENSITY | FOREGROUND_RED, ControlScheme('o', 'k', 'l', 'm', 'n'), Vector2(_window.GetBufferSize().X - 10, _window.GetBufferSize().Y / 2));

	//start frame timer
	WindowsTimer frameTimer{};
	frameTimer.Start();

	// === Main Game Loop ===
	while (!_gameHasEnded) 
	{
		float deltaTime = frameTimer.GetElapsedSeconds(true);
		
		//=== update game logic ===
		
		_window.Update();

		//check for colliding entities ( complexity : O(n2/2) )
		std::map<Entity*, std::vector<Entity*>> collidingEntities;
		for (int i = 0; i < _entities.size(); i++)
		{
			for(int j = i+1;j < _entities.size(); j++)
			{
				if (i == j) continue;
				const Entity& entityA = *_entities[i];
				const Entity& entityB = *_entities[j];
				if (!(entityA.IsActive() && entityB.IsActive())) continue;

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

		//update entities
		for (auto pEntity : _entities) {
			if(pEntity->IsActive())
				pEntity->Update({deltaTime,_window,collidingEntities});
		}

		//=== draw game ===

		_window.Clear();
		_window.Blit(_backgroundSprite.GetData());
		for (auto& rEntity : _entities) {
			if (rEntity->IsActive())
				rEntity->Draw(_window);
		}
		_window.EndFrame();

		//todo : have _gameHasEnded be true only if one of the two ships has been destroyed
		const KeyboardInputData* victoryInputs = _window.GetInputs();
		if (victoryInputs->IsKeyHeld('w')) {
			_gameHasEnded = true;
		}
	}
	return PlayVictoryScreen();
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


bool Game::PlayVictoryScreen()
{
	_entities.clear();
	_window.Clear();

	//todo : switch win sprite depending on who won
	Sprite winSprite{ "win1.txt",BACKGROUND_GREEN };


	_window.Blit(winSprite.GetData());
	_window.EndFrame();

	while (true) {
		if (TryToReplay()) break;
	}
	return _gameHasEnded;
}

bool Game::TryToReplay()
{
	_window.Update();
	const KeyboardInputData* victoryInputs = _window.GetInputs();
	if (victoryInputs->IsKeyHeld(' ')) {
		_gameHasEnded = false;
		return true;
	}
	if (victoryInputs->IsKeyHeld('x')) {
		_gameHasEnded = true;
		return true;
	}
	return false;
}