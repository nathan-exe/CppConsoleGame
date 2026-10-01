#include "Game.h"
#include <wincontypes.h>
#include <src/Entities/Ship.h>
#include <src/Entities/Entity.h>
#include <src/Window/Window.h>
#include <src/Maths/WindowsTimer.h>

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

		for (auto& rEntity : _entities) {
			if(rEntity->IsActive()) rEntity->Update(timePassed, _window.GetInputs());
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
