#pragma once
namespace Math
{
	int Random(int min, int max);
	template<typename T = float>
	float Random(T min, T max);
	float Sign(float value);
	float Clamp(float value, float min, float max);
	Vector2 RotateVector2(Vector2 vector, float rot);
	float Distance(Vector2 vector);
	float Direction(Vector2 from, Vector2 to);
}