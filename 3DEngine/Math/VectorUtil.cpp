#include "VectorUtil.h"

ENGINE_NAMESPACE_START

float VectorUtil::dot(const Vector3 & lhs, const Vector3 & rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

Vector3 VectorUtil::cross(const Vector3 & lhs, const Vector3 & rhs)
{
	Vector3 result;
	result.x = lhs.y * rhs.z - lhs.z * rhs.y;
	result.y = lhs.z * rhs.x - lhs.x * rhs.z;
	result.z = lhs.x * rhs.y - lhs.y * rhs.x;
	return result;
}

ENGINE_NAMESPACE_END