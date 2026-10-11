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

	bool operator==(Vector2 other);
	
	static float Dot(Vector2 A, Vector2 B);
	static float DistanceBetweenPoints(Vector2 A, Vector2 B);
	static Vector2 ProjectPointOnSegment(Vector2 Point, Vector2 segA, Vector2 segB);
	static float GetDistanceToSegment(Vector2 Point, Vector2 segA, Vector2 segB);
	static float GetDistanceBetweenSegments(std::pair<Vector2,Vector2> seg0, std::pair<Vector2, Vector2> seg1);

	float x;
	float y;
};

