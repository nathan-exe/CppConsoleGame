#include "Vector2.h"

Vector2::Vector2(float X, float Y)
	: x(X), y(Y)
{
}

Vector2 Vector2::operator+(Vector2 other)
{
	return {x+other.x,y+other.y};
}

Vector2 Vector2::operator-(Vector2 other)
{
	return { x - other.x,y - other.y };
}

Vector2 Vector2::operator*(float other)
{
	return {x * other, y * other};
}

Vector2 Vector2::operator/(float other)
{
	return *this * (1.0f / other);
}
