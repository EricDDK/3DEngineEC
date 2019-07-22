#include "Quaternion.h"
#include <cmath>

ENGINE_NAMESPACE_START

Quaternion::Quaternion()
{
	*this = Quaternion::Identity;
}

Quaternion::~Quaternion()
{

}

Quaternion::Quaternion(float qX, float qY, float qZ, float qW)
{
	set(qX, qY, qZ, qW);
}

Quaternion::Quaternion(const Quaternion& rhs)
{
	set(rhs.x, rhs.y, rhs.z, rhs.w);
}

Quaternion::Quaternion(const Vector3& axis, float theta)
{
	float scalar = std::sin(theta / 2.0f);
	x = axis.x * scalar;
	y = axis.y * scalar;
	z = axis.z * scalar;
	w = std::cos(theta / 2.0f);
}

void Quaternion::set(float qX, float qY, float qZ, float qW)
{
	x = qX;
	y = qY;
	z = qZ;
	w = qW;
}

void Quaternion::conjugate()
{
	x *= -1.0f;
	y *= -1.0f;
	z *= -1.0f;
}

float Quaternion::lengthSq() const
{
	return (x * x + y * y + z * z);
}

float Quaternion::length() const
{
	return std::sqrt(lengthSq());
}

void Quaternion::normalize()
{
	float l = length();
	x /= l;
	y /= l;
	z /= l;
	w /= l;
}

float Quaternion::dot(const Quaternion& lhs, const Quaternion& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

Quaternion Quaternion::normalize(const Quaternion& rhs)
{
	Quaternion result = rhs;
	result.normalize();
	return result;
}

Quaternion Quaternion::lerp(const Quaternion& lhs, const Quaternion& rhs, float angle)
{
	Quaternion result;
	result.x = lhs.x + angle * (rhs.x - lhs.x);
	result.y = lhs.y + angle * (rhs.y - lhs.y);
	result.z = lhs.z + angle * (rhs.z - lhs.z);
	result.w = lhs.w + angle * (rhs.w - lhs.w);
	return result;
}

Quaternion Quaternion::slerp(const Quaternion& lhs, const Quaternion& rhs, float angle)
{
	float rawCosm = Quaternion::dot(lhs, rhs);

	float cosom = -rawCosm;
	if (rawCosm >= 0.0f)
	{
		cosom = rawCosm;
	}

	float scale0, scale1;

	if (cosom < 0.9999f)
	{
		const float omega = std::acos(cosom);
		const float invSin = 1.f / std::sin(omega);
		scale0 = std::sin((1.f - angle) * omega) * invSin;
		scale1 = std::sin(angle * omega) * invSin;
	}
	else
	{
		// Use linear interpolation if the quaternions
		// are collinear
		scale0 = 1.0f - angle;
		scale1 = angle;
	}

	if (rawCosm < 0.0f)
	{
		scale1 = -scale1;
	}

	Quaternion retVal;
	retVal.x = scale0 * lhs.x + scale1 * rhs.x;
	retVal.y = scale0 * lhs.y + scale1 * rhs.y;
	retVal.z = scale0 * lhs.z + scale1 * rhs.z;
	retVal.w = scale0 * lhs.w + scale1 * rhs.w;
	retVal.normalize();
	return retVal;
}

Quaternion Quaternion::concatenate(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion retVal;

	// Vector component is:
	// ps * qv + qs * pv + pv x qv
	Vector3 qv(lhs.x, lhs.y, lhs.z);
	Vector3 pv(rhs.x, rhs.y, rhs.z);
	Vector3 newVec = qv * rhs.w + pv * lhs.w + Vector3::cross(pv, qv);
	retVal.x = newVec.x;
	retVal.y = newVec.y;
	retVal.z = newVec.z;

	// Scalar component is:
	// ps * qs - pv . qv
	retVal.w = rhs.w * lhs.w - Vector3::dot(pv, qv);

	return retVal;
}

const Quaternion Quaternion::Identity(0.0f, 0.0f, 0.0f, 1.0f);

ENGINE_NAMESPACE_END