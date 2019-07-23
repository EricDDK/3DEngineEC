#ifndef __MATH_MATH_H__
#define __MATH_MATH_H__

#include "../Common/Macro.h"
#include "Vector2.h"
#include "MathCommon.h"

ENGINE_NAMESPACE_START

namespace math {

	template <typename T>
	inline bool nearZero(T val)
	{
		if (val <= 0.001f)
			return true;
		else
			return false;
	}

	template <typename T>
	inline float toRadians(T degress)
	{
		return degress * PI / 180.0f;
	}

}

ENGINE_NAMESPACE_END

#endif