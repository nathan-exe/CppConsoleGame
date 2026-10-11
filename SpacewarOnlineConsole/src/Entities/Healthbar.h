#pragma once
#include "src/Entities/Entity.h"

//Include Librairie Statique
#include "WindowLibrary.h"

class Healthbar : public Entity
{
public :
	Healthbar(int maxHP, bool drawLeftToRight,WORD color);
	void Draw(WindowLibrary::ConsoleWindow& rWindow) override;
	void Update(UpdateContext ctx) override;
	void Diminish(char amount);
	void Replenish(char amount);
	void FlipGraphics();

	inline bool IsEmpty() const { return _hp == 0; }

private : 
	const char _maxHP;
	char _hp;
	const WORD _color;
	bool _drawLeftToRight;

};

