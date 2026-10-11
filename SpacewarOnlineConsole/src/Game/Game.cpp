#include "Game.h"
#include "src/Maths/Vector2.h"
#include <wincontypes.h>
#include <src/Entities/Ship.h>
#include <src/Entities/Entity.h>
#include <src/Maths/WindowsTimer.h>
#include <map>
#include <iostream>

//Include Librairie Statique
#include "ConsoleWindow.h"

Game* Game::s_pSingletonInstance = nullptr;

Game::Game() 
: _gameHasEnded (false)
{
	s_pSingletonInstance = this;
}

Game::~Game()
{
	s_pSingletonInstance = nullptr;
}



bool Game::RunAndAskForReplay()
{
	// === Game Initialisation ===

	//load sprites
	Sprite _backgroundSprite{ "background.txt", FOREGROUND_BLUE };

	//create player ships
	Ship player1(FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN, ControlScheme('e', 's', 'd', 'f', 'w'), Vector2(10, _window.GetBufferSize().Y / 2));
	Ship player2(FOREGROUND_INTENSITY | FOREGROUND_RED, ControlScheme('i', 'j', 'k', 'l', ':'), Vector2(_window.GetBufferSize().X - 10, _window.GetBufferSize().Y / 2));

	//start frame timer
	WindowsTimer frameTimer{};
	frameTimer.Start();

	// === Main Game Loop ===
	while (!_gameHasEnded) 
	{
		float deltaTime = frameTimer.GetElapsedSeconds(true);
		
		//=== update game logic ===
		
		_window.Update();

		//check for colliding entities 
		std::map<Entity*, std::vector<Entity*>> collidingEntities = GetCollidingEntities();

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


	}

	bool playAgain = ShowVictoryScreenAndAskForReplay();
	return playAgain;
}

void Game::End()
{
	_gameHasEnded = true;
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


std::map<Entity*, std::vector<Entity*>> Game::GetCollidingEntities()
{
	std::map<Entity*, std::vector<Entity*>> output;

	//for each unique entity pair ( complexity : O(n2/2) )
	for (int i = 0; i < _entities.size(); i++)
	{
		for (int j = i + 1;j < _entities.size(); j++)
		{
			if (i == j) continue;
			const Entity& entityA = *_entities[i];
			const Entity& entityB = *_entities[j];
			if (!(entityA.IsActive() && entityB.IsActive())) continue;

			//Check for capsule-capsule intersection
			//where each capsule is defined by the entity's current and last frame position.
			//This allows for continuous collision detection between fast moving circular colliders.
			const float distanceBetweenSegments = Vector2::GetDistanceBetweenSegments(
				{ entityA.GetPosition(),entityA.GetOldPosition() },
				{ entityB.GetPosition(),entityB.GetOldPosition() }
			);
			const bool capsulesOverlapEachother = distanceBetweenSegments <= entityA.GetCollisionRadius() + entityB.GetCollisionRadius();

			//register overlapping entity pairs
			if (capsulesOverlapEachother) {
				output[_entities[i]].push_back(_entities[j]);
				output[_entities[j]].push_back(_entities[i]);
			}
		}
	}

	return output;
}

bool Game::ShowVictoryScreenAndAskForReplay()
{
	_entities.clear();
	_window.Clear();

	//todo : switch win sprite depending on who won
	Sprite winSprite{ "win1.txt",BACKGROUND_GREEN };

	_window.Blit(winSprite.GetData());
	_window.EndFrame();

	return GetReplayAnswer();
}

bool Game::GetReplayAnswer()
{
	_window.ResetInputMode();
	std::string c;

	std::cout << "Enter \"Replay\" to restart the game.\nEnter \"Stop\" to exit the application."<<std::endl; //(temporaire en attendant un sprite)
	while (std::cin >> c) {
		if (c == "Replay")
			return true;
		else if (c == "Stop")
			return false;
	}

	throw std::runtime_error("Bad cin.");
	
}