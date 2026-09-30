#include "Game.h"
#include <wincontypes.h>

void Game::Run()
{
	static float deltaTime = 0;

	while (true) {

		//todo : start deltatime timer

		//=== update game logic ===
		
		_window.Update();
		for (auto& rEntity : _entities) {
			rEntity.Update(deltaTime);
		}

		//=== draw game ===

		_window.BeginFrame();
		for (auto& rEntity : _entities) {
			rEntity.Draw(_window);
		}
		_window.EndFrame();

		//todo : end deltatime timer and retrieve value
	}
}
