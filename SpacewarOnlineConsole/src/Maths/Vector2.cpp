#include "Vector2.h"
#include <cmath>

Vector2::Vector2() : x(0), y(0) {};

Vector2::Vector2(float X, float Y)
	: x(X), y(Y)
{
}

float Vector2::GetMagnitude()
{
	return std::sqrt(x*x + y*y);
}

Vector2 Vector2::GetNormalizedVector()
{
	float magnitude = GetMagnitude();
	Vector2 result{};

	if (magnitude > 0) {
		result = *this / magnitude;
	}
	return result;
}

//Retourner un vecteur avec magnitude donnée
Vector2 Vector2::WithMagnitude(float magnitude)
{
	return GetNormalizedVector() * magnitude;
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
