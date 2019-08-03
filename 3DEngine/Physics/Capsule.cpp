#include "Capsule.h"

ENGINE_NAMESPACE_START

Capsule::Capsule(const Vector3& start, const Vector3& end, float r)
	: lineSegment(start, end)
	, radius(r)
{

}

Vector3 Capsule::PointOnSegment(float t) const
{
	return lineSegment.pointOnSegment(t);
}

bool Capsule::Contains(const Vector3& point) const
{
	// Get minimal dist. sq. between point and line segment
	float distSq = lineSegment.minDistSq(point);
	return distSq <= (radius * radius);
}

ENGINE_NAMESPACE_END