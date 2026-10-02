#pragma once
#include "src/Window/Window.h"
#include <vector>
#include <string>

class Sprite
{
public :
	Sprite() = default;
	Sprite(std::string filename, WORD attributes);
	Sprite(int sizeX, int sizeY, std::vector<CHAR_INFO> display);

	void Draw(GameWindow& rWindow, int positionX, int positionY);

	//Accessors
	inline CHAR_INFO* GetData() { return _charData.data(); }
private:
	int _width;
	int _height;
	std::vector<CHAR_INFO> _charData;
};

