#pragma once
#include "src/Entities/Entity.h"

class Healthbar : public Entity
{
public :
	Healthbar(int maxHP, bool drawLeftToRight,WORD color);
	void Draw(GameWindow& rWindow) override;
	void Update(UpdateContext ctx) override;
	void Diminish(char amount);
	void Replenish(char amount);
	void FlipGraphics();

	inline bool IsEmpty() { return _hp == 0; }

private : 
	const char _maxHP;
	char _hp;
	const WORD _color;
	bool _drawLeftToRight;

};

