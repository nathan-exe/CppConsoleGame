#include "Vector2.h"
#include <cmath>
#include <algorithm>

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

float Vector2::Dot(Vector2 A, Vector2 B)
{
	return A.x*B.x+A.y*B.y;
}

float Vector2::DistanceBetweenPoints(Vector2 A, Vector2 B)
{
	return (A - B).GetMagnitude();
}

Vector2 Vector2::ProjectPointOnSegment(Vector2 Point, Vector2 A, Vector2 B)
{
	Vector2 AB = B - A;
	Vector2 AM = Point - A;
	float t = Dot(AB, AM) / Dot(AM, AM);
	t = std::max(0.0f, std::min(t, AB.GetMagnitude()));
	return A + AB * t;
}

float Vector2::GetDistanceToSegment(Vector2 Point, Vector2 A, Vector2 B)
{
	return DistanceBetweenPoints(Point,ProjectPointOnSegment(Point,A,B));
}

float Vector2::GetDistanceBetweenSegments(std::pair<Vector2, Vector2> seg0, std::pair<Vector2, Vector2> seg1)
{
	Vector2 A0 = seg0.first;
	Vector2 B0 = seg0.second;
	Vector2 A1 = seg0.first;
	Vector2 B1 = seg0.second;

	float distances[4]{
		GetDistanceToSegment(A0, A1, B1),
		GetDistanceToSegment(B0, A1, B1),
		GetDistanceToSegment(A1, A0, B0),
		GetDistanceToSegment(B1, A0, B0)
	};

		return *std::min_element(
		std::begin(distances),
		std::end(distances));
	
}
