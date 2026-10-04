#pragma once
#include <vector>
#include <string>
#include <windows.h>

class ConsoleWindow;
class Sprite
{
public :
	Sprite() = default;
	Sprite(std::string filename, WORD attributes);
	/*Sprite(const Sprite& other) = delete;
	Sprite(Sprite&& other) = delete;*/
	~Sprite();

	void Draw(ConsoleWindow& rWindow, int positionX, int positionY);

	//Accessors
	inline CHAR_INFO* GetData() { return _charData; }
private:
	int _width;
	int _height;
	
	CHAR_INFO* _charData = nullptr; //heap allocated array of char_infos
};

