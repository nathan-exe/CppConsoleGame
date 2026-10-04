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
    ~Game();

	bool RunAndAskForReplay();
    void End();
    void RegisterEntity(Entity* entity);
    void UnregisterEntity(Entity* entity);

    inline static Game& GetInstance() {return *s_pInstance;}
    inline GameWindow& GetWindow() { return _window; }

private : 
    static Game* s_pInstance;
	GameWindow _window;
	std::vector<Entity*> _entities;

    bool _gameHasEnded;

    bool ShowVictoryScreenAndAskForReplay();
    bool GetReplayAnswer();
};

