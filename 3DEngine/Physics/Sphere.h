#ifndef _PHYSICS_SPHERE_H__
#define _PHYSICS_SPHERE_H__

#include "../Common/Macro.h"
#include "../Math/Math.h"

ENGINE_NAMESPACE_START

class Sphere
{
public:

	Vector3 center;

	float radius;

	Sphere(const Vector3& cen, float rad);

	bool contains(const Vector3& point) const;

};

ENGINE_NAMESPACE_END

#endif