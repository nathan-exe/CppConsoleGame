#include "Sprite.h"
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

//Include Librairie Statique
#include "WindowLibrary.h"

Sprite::Sprite(std::string filename, WORD attributes)
{
	//std::filesystem::path cwd = std::filesystem::current_path() / "filename.txt";
	//std::ofstream file(cwd.string());
	//file.close();

	const char SPACE = ':';
	const char* pathToSprites = "resources/";

	std::ifstream input;

	input.open(pathToSprites + filename);

	input >> _width;
	input >> _height;

	size_t dataLength = _width * _height;
	_charData = new CHAR_INFO[dataLength];

	std::string tmp;
	size_t i = 0;
	while (!(input >> tmp).fail()) {
		for (char c : tmp)
		{
			CHAR_INFO charinfo{};

			if (c == SPACE) 
			{
				c = ' ';
			}
			else {
				charinfo.Attributes = attributes;
			}
			
			charinfo.Char.AsciiChar = c;
			
			if(i< dataLength)
				*(_charData + i++) = charinfo;
		}
	}
	input.close();
}

Sprite::~Sprite()
{
	if(_charData != nullptr)
		delete[] _charData;
}

void Sprite::Draw(WindowLibrary::ConsoleWindow& rWindow, int positionX, int positionY)
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
