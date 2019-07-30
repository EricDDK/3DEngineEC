#ifndef _PHYSICS_PLANE_H__
#define _PHYSICS_PLANE_H__

#include "../Common/Macro.h"
#include "../Math/Math.h"

ENGINE_NAMESPACE_START

class Plane
{
public:

	// Normal vector of the plane.
	Vector3 normal;

	// Distance from the origin to the plane.
	float distance;

	Plane(const Vector3& nor, float d);

	Plane(const Vector3& a, const Vector3& b, const Vector3& c);

	float getDistance(const Vector3& point) const;

};

ENGINE_NAMESPACE_END

#endif