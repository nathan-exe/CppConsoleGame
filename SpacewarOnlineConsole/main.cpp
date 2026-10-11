// SpacewarOnlineConsole.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <windows.h>
#include <src/Game/Game.h>

//Include Librairie Statique
#include "WindowLibrary.h"

int main()
{

    try {
        bool isPlaying = true;
        while (isPlaying) {
            Game game{};
            isPlaying = game.RunAndAskForReplay();
        }
    }
    //catch windows related exceptions
    catch (WindowLibrary::WindowsException e) {
        MessageBoxA(NULL, e.what(), "Error", MB_OK);
        return (e.GetErrorCode());
    }
    //catch other exceptions
    catch (std::exception e) {
        //display error message box with exception message
        MessageBoxA(NULL, e.what(), "Error", MB_OK);
        return EXIT_FAILURE;
    }

	

    return EXIT_SUCCESS;
	
}