#include "Math/Vector3.h"
#include <cmath>
#include "MathCommon.h"

ENGINE_NAMESPACE_START

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::~Vector3()
{

}

Vector3::Vector3(float tX, float tY, float tZ)
{
	x = tX;
	y = tY;
	z = tZ;
}

Vector3::Vector3(const Vector3& v)
{
	set(v);
}

Vector3 Vector3::operator=(const Vector3& v)
{
	set(v);
	return *this;
}

void Vector3::set(float tX, float tY, float tZ)
{
	x = tX;
	y = tY;
	z = tZ;
}

void Vector3::set(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3 Vector3::operator+(const Vector3& v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

float Vector3::operator*(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::operator*(float scale) const
{
	return Vector3(x * scale, y * scale, z * scale);
}

Vector3 Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3 Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3 Vector3::operator*=(const Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

Vector3 Vector3::operator*=(float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
	return *this;
}

bool Vector3::operator==(const Vector3& v)
{
	return x == v.x && y == v.y && z == v.z;
}

bool Vector3::operator!=(const Vector3& v)
{
	return !((*this) == v);
}

Vector3 Vector3::lerp(const Vector3& other, float alpha) const
{
	return *this * (1.f - alpha) + other * alpha;
}

float Vector3::distance()
{
	float n = x * x + y * y + z * z;
	return std::sqrt(n);
}

void Vector3::normalize()
{
	float n = x * x + y * y + z * z;
	if (n == 1.0f)
		return;
	n = std::sqrt(n);
	if (n < MATH_TOLERANCE)
		return;
	n = 1.0f / n;
	x *= n;
	y *= n;
	z *= n;
}

ENGINE_NAMESPACE_END