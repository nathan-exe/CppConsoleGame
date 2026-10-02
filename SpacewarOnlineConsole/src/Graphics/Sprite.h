#pragma once
#include "src/Window/Window.h"
#include <vector>
class Sprite
{
public :
	Sprite() = default;
	Sprite(int sizeX, int sizeY, std::vector<CHAR_INFO> display);
	void Draw(GameWindow& rWindow, int positionX, int positionY);
private:
	int _sizeX;
	int _sizeY;
	std::vector<CHAR_INFO> _sprite;
};

