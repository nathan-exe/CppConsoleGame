#pragma once
#include <utility>
class Vector2
{
public : 
	
	static Vector2 operator+(Vector2 a, Vector2 b);
	static Vector2 operator-(Vector2 a, Vector2 b);
	static Vector2 operator*(Vector2 a, float b);
	static Vector2 operator/(Vector2 a, float b);

private :
	float _x;
	float _y;
};

