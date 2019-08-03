#ifndef _PHYSICS_CAPSULE_H__
#define _PHYSICS_CAPSULE_H__

#include "../Common/Macro.h"
#include "../Math/Math.h"
#include "LineSegment.h"

ENGINE_NAMESPACE_START

class Capsule
{
public:

	LineSegment lineSegment;

	float radius;

	Capsule() = delete;

	Capsule(const Vector3& start, const Vector3& end, float radius);

	Vector3 PointOnSegment(float t) const;

	bool Contains(const Vector3& point) const;

};

ENGINE_NAMESPACE_END

#endif