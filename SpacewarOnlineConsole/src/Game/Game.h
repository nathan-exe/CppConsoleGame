#pragma once
#include <vector>
#include <map>
#include "src/Window/Window.h"
#include "src/Entities/Entity.h"

class Entity;
class Game
{
public:
    Game();

	void Run();
    void RegisterEntity(Entity* entity);
    void UnregisterEntity(Entity* entity);

    inline static Game& GetInstance() {return *instance;}
    inline GameWindow& GetWindow() { return _window; }

private : 
    static Game* instance;
	GameWindow _window;
	std::vector<Entity*> _entities;

};

