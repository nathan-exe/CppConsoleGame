#pragma once
#include <vector>
#include <src/Window/Window.h>
#include "src/Entities/Entity.h"

class Game
{
public : 
    Game();
	void Run();

    static Game& GetInstance() {
        return *instance;
    }


    void RegisterEntity(Entity* entity);

    void UnregisterEntity(Entity* entity);
private : 
	GameWindow _window;
	std::vector<Entity*> _entities;

    static Game* instance;
};

