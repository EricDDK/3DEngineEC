#ifndef __MATH_VECTOR_UTIL_H__
#define __MATH_VECTOR_UTIL_H__

#include "Vector3.h"

#include "../Common/Macro.h"

ENGINE_NAMESPACE_START

class VectorUtil
{
public:
	static float dot(const Vector3& lhs, const Vector3& rhs);

	static Vector3 cross(const Vector3& lhs, const Vector3& rhs);
};

ENGINE_NAMESPACE_END

#endif