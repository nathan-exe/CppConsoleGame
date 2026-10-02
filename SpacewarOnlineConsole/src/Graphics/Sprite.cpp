#include "Sprite.h"

Sprite::Sprite(int sizeX, int sizeY, std::vector<CHAR_INFO> display)
{
	_sizeX = sizeX;
	_sizeY = sizeY;
	_sprite = display;
}

void Sprite::Draw(GameWindow& rWindow, int positionX, int positionY)
{
	int cornerX = positionX - (_sizeX / 2);
	int cornerY = positionY - (_sizeY / 2);

	COORD size = rWindow.GetBufferSize();

	for (int y = 0; y <  _sizeY; y++) {
		for (int x = 0; x < _sizeX; x++) {
			if (!((cornerX + x < 0 || cornerX > size.X) || (cornerY + y < 0 || cornerY + y > size.Y))) {
				rWindow.SetChar(cornerX + x, cornerY + y, _sprite[x + y * _sizeX]);
			}
		}
	}
}
