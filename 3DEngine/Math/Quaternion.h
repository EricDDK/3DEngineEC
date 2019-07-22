#ifndef __MATH_QUATERNION_H__
#define __MATH_QUATERNION_H__

#include "Vector3.h"

#include "../Common/Macro.h"

ENGINE_NAMESPACE_START

class Quaternion
{
public:
	float x;

	float y;

	float z;

	float w;

	Quaternion();

	~Quaternion();

	Quaternion(float qX, float qY, float qZ, float qW);

	Quaternion(const Quaternion& rhs);

	Quaternion(const Vector3& v, float angle);

	void set(float qX, float qY, float qZ, float qW);

	void conjugate();

	float lengthSq() const;

	float length() const;

	void normalize();

	static float dot(const Quaternion& lhs, const Quaternion& rhs);

	static Quaternion normalize(const Quaternion& rhs);

	static Quaternion lerp(const Quaternion& lhs, const Quaternion& rhs, float angle);

	static Quaternion slerp(const Quaternion& lhs, const Quaternion& rhs, float angle);

	//Rotate by lhs FOLLOWED BY rhs
	static Quaternion concatenate(const Quaternion& lhs, const Quaternion& rhs);

	static const Quaternion Identity;

};

ENGINE_NAMESPACE_END

#endif