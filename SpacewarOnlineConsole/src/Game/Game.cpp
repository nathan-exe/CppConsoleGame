#include "Game.h"
#include <wincontypes.h>
#include <src/Entities/Ship.h>
#include <src/Entities/Entity.h>
#include <src/Window/Window.h>
#include <src/Maths/WindowsTimer.h>

void Game::Run()
{
	Ship shipp{};

	_entities.push_back(&shipp);

	//static float deltaTime = 0;

	WindowsTimer timer{};
	timer.Start();

	while (true) {

		//todo : start deltatime timer
		float timePassed = timer.GetElapsedSeconds(true);
		


		//=== update game logic ===
		
		_window.Update();
		for (auto& rEntity : _entities) {
			rEntity->Update(timePassed,_window.GetInputs());
		}

		//=== draw game ===

		_window.BeginFrame();
		for (auto& rEntity : _entities) {
			rEntity->Draw(_window);
		}

		//CHAR_INFO charinf{};
		//charinf.Char.AsciiChar = 'A';
		//charinf.Attributes = 0x0E;

		//_window.SetChar(5, 5, charinf);

		_window.EndFrame();

		//todo : end deltatime timer and retrieve value
	}
}
