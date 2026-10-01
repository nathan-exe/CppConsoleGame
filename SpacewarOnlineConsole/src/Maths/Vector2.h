#pragma once
#include <utility>
class Vector2
{
public : 

	Vector2(float x, float y);

	Vector2();

	float GetMagnitude();

	Vector2 GetNormalizedVector();

	Vector2 WithMagnitude(float magnitude);

	Vector2 operator+(Vector2 other);
	Vector2 operator-(Vector2 other);
	Vector2 operator*(float b);
	Vector2 operator/(float b);
	
	float x;
	float y;
};

