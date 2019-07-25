#include "Math/Vector3.h"
#include "Quaternion.h"
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

const float * Vector3::getShaderPtr() const
{
	return reinterpret_cast<const float*>(&x);
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

Vector3 Vector3::normalize(const Vector3& vec)
{
	Vector3 result = vec;
	result.normalize();
	return result;
}

float Vector3::dot(const Vector3& lhs, const Vector3& rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

Vector3 Vector3::cross(const Vector3& lhs, const Vector3& rhs)
{
	Vector3 result;
	result.x = lhs.y * rhs.z - lhs.z * rhs.y;
	result.y = lhs.z * rhs.x - lhs.x * rhs.z;
	result.z = lhs.x * rhs.y - lhs.y * rhs.x;
	return result;
}

Vector3 Vector3::transform(const Vector3& v, const Quaternion& q)
{
	Vector3 result = v;
	Vector3 qv(q.x, q.y, q.z);
	result += Vector3::cross(qv, Vector3::cross(qv, v) + v * q.w) * 2.0f;
	return result;
}

Vector3 Vector3::transform(const Vector3& v, const Matrix4& m, float w)
{
	Vector3 result;
	// TODO
	EC_ASSERT(0 == 1);
	return result;
}

const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);

ENGINE_NAMESPACE_END