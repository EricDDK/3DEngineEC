#include "Math/Vector2.h"
#include <cmath>
#include "MathCommon.h"

ENGINE_NAMESPACE_START

Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::~Vector2()
{

}

Vector2::Vector2(float tX, float tY)
{
	x = tX;
	y = tY;
}

Vector2::Vector2(const Vector2& v)
{
	set(v);
}

Vector2 Vector2::operator=(const Vector2& v)
{
	set(v);
	return *this;
}

void Vector2::set(float tX, float tY)
{
	x = tX;
	y = tY;
}

void Vector2::set(const Vector2& v)
{
	x = v.x;
	y = v.y;
}

Vector2 Vector2::operator+(const Vector2& v) const
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(x - v.x, y - v.y);
}

float Vector2::operator*(const Vector2& v) const
{
	return x * v.x + y * v.y;
}

Vector2 Vector2::operator*(float scale) const
{
	return Vector2(x * scale, y * scale);
}

Vector2 Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2 Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2 Vector2::operator*=(const Vector2& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

Vector2 Vector2::operator*=(float scale)
{
	x *= scale;
	y *= scale;
	return *this;
}

bool Vector2::operator==(const Vector2& v)
{
	return x == v.x && y == v.y;
}

bool Vector2::operator!=(const Vector2& v)
{
	return !((*this) == v);
}

Vector2 Vector2::lerp(const Vector2& other, float alpha) const
{
	return *this * (1.f - alpha) + other * alpha;
}

float Vector2::lengthSq()
{
	return x * x + y * y;
}

float Vector2::length()
{
	float n = x * x + y * y;
	return std::sqrt(n);
}

void Vector2::normalize()
{
	float n = x * x + y * y;
	if (n == 1.0f)
		return;
	n = std::sqrt(n);
	if (n < MATH_TOLERANCE)
		return;
	n = 1.0f / n;
	x *= n;
	y *= n;
}

float Vector2::dot(const Vector2& a, const Vector2& b)
{
	return (a.x * b.x + a.y * b.y);
}

ENGINE_NAMESPACE_END