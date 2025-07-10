#include "Vector2.h"


Vector2::Vector2(void)
{
	x = y = 0; // ïœêîèâä˙âª
}

Vector2::Vector2(const int& X, const int& Y)
{
	x = X;
	y = Y;
}

#pragma region élë•ââéZ

Vector2 Vector2::operator+(const Vector2& vec)const
{
	return Vector2{ (x + vec.x), (y + vec.y) };
}

void Vector2::operator+=(const Vector2& vec)
{
	x += vec.x;
	y += vec.y;
}

Vector2 Vector2::operator-(const Vector2& vec)const
{
	return Vector2{ (x - vec.x), (y - vec.y) };
}

void Vector2::operator-=(const Vector2& vec)
{
	x -= vec.x;
	y -= vec.y;
}

Vector2 Vector2::operator*(const Vector2& vec)const
{
	return Vector2{ (x * vec.x), (y * vec.y) };
}

void Vector2::operator*=(const Vector2& vec)
{
	x *= vec.x;
	y *= vec.y;
}

Vector2 Vector2::operator/(const Vector2& vec)const
{
	return Vector2{ (x / vec.x), (y / vec.y) };
}

void Vector2::operator/=(const Vector2& vec)
{
	x /= vec.x;
	y /= vec.y;
}
#pragma endregion