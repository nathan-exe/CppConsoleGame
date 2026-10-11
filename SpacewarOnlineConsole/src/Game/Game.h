#pragma once
#include <vector>
#include <map>
#include "src/Entities/Entity.h"
#include "Typedefs.h"

//Include Librairie Statique
#include "ConsoleWindow.h"

/// <summary>
/// A class that holds all of the game's data and entities.
/// This class is where the game takes place.
/// </summary>
class Game
{
public:
    Game();
    ~Game();

	/// <summary>
	/// the whold game is ran into this method.
    /// it returns true if the players ask to play again at the end.
	/// </summary>
	/// <returns></returns>
	bool RunAndAskForReplay();
    void End();

    /// <summary>
    /// registers an entity to be updated and drawn each frame.
    /// </summary>
    /// <param name="entity"></param>
    void RegisterEntity(Entity* entity);
    void UnregisterEntity(Entity* entity);

    //getters
    inline WindowLibrary::ConsoleWindow& GetWindow() { return _window; }
    inline static Game& GetSingletonInstance() {return *s_pSingletonInstance;}

private : 
    static Game* s_pSingletonInstance;
	WindowLibrary::ConsoleWindow _window;
	std::vector<Entity*> _entities;

    bool _gameHasEnded;

    std::map<Entity*, std::vector<Entity*>> GetCollidingEntities();
    bool ShowVictoryScreenAndAskForReplay();
    bool GetReplayAnswer();
};

