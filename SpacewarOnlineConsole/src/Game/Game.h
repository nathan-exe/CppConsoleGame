#pragma once
#include <vector>
#include <src/Window/Window.h>
#include "src/Entities/Entity.h"

class Game
{
public : 
	void Run();

private : 
	GameWindow _window;
	std::vector<Entity*> _entities;

};

