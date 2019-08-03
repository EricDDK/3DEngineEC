#include "Plane.h"

ENGINE_NAMESPACE_START

Plane::Plane(const Vector3& nor, float d)
	: normal(nor)
	, distance(d)
{

}

Plane::Plane(const Vector3& a, const Vector3& b, const Vector3& c)
{
	// Compute vectors from a to b and a to c
	Vector3 ab = b - a;
	Vector3 ac = c - a;
	// Cross product and normalize to get normal
	normal = Vector3::cross(ab, ac);
	normal.normalize();
	// d = -P dot n
	distance = -Vector3::dot(a, normal);
}

float Plane::getDistance(const Vector3& point) const
{
	return Vector3::dot(point, normal) - distance;
}

ENGINE_NAMESPACE_END