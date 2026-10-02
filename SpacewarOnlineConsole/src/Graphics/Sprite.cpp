#include "Sprite.h"
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <iostream>

Sprite::Sprite(std::string filename, WORD attributes)
{
	//std::filesystem::path cwd = std::filesystem::current_path() / "filename.txt";
	//std::ofstream file(cwd.string());
	//file.close();

	const char emptyEquivalentChar = ':';
	const char* pathToSprites = "resources/";

	std::ifstream input;

	input.open(pathToSprites + filename);

	input >> _width;
	input >> _height;

	std::string value;

	while (!(input >> value).fail()) {
		for (char a : value)
		{
			CHAR_INFO charinfo{};

			if (a == emptyEquivalentChar) 
			{
				a = ' ';
			}
			else {
				charinfo.Attributes = attributes;
			}
			
			charinfo.Char.AsciiChar = a;
			
			_charData.push_back(charinfo);
		}
	}
	input.close();
}

Sprite::Sprite(int sizeX, int sizeY, std::vector<CHAR_INFO> display)
{
	_width = sizeX;
	_height = sizeY;
	_charData = display;
}

void Sprite::Draw(GameWindow& rWindow, int positionX, int positionY)
{
	const int cornerX = positionX - (_width / 2);
	const int cornerY = positionY - (_height / 2);

	const COORD size = rWindow.GetBufferSize();

	for (int y = 0; y <  _height; y++) {
		for (int x = 0; x < _width; x++) 
		{
			if (rWindow.ContainsPoint(cornerX + x, cornerY + y) && _charData[x + y * _width].Char.AsciiChar !=' ') {
				rWindow.SetChar(cornerX + x, cornerY + y, _charData[x + y * _width]);
			}
		}
	}
}
