#ifndef _COMMON_AABB_H__
#define _COMMON_AABB_H__

#include "../Common/Macro.h"
#include "../Math/Math.h"

ENGINE_NAMESPACE_START

class AABB
{
public:

	AABB(const Vector3& min, const Vector3& max);

	virtual ~AABB();

	void update(const Vector3& point);

	void rotate(const Quaternion& q);

	bool contain(const Vector3& point);

	Vector3 min;

	Vector3 max;

};

ENGINE_NAMESPACE_END

#endif