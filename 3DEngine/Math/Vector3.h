#ifndef __MATH_VECTOR3_H__
#define __MATH_VECTOR3_H__

#include "../Common/Macro.h"

ENGINE_NAMESPACE_START

class Vector3
{
public:

	float x;

	float y;

	float z;

	Vector3();

	~Vector3();

	Vector3(float tX, float tY, float tZ);

	Vector3(const Vector3& v);

	Vector3 operator=(const Vector3& v);

	void set(float tX, float tY, float tZ);

	void set(const Vector3& v);

	Vector3 operator+(const Vector3& v) const;

	Vector3 operator-(const Vector3& v) const;

	float operator*(const Vector3& v) const;

	Vector3 operator*(float scale) const;

	Vector3 operator+=(const Vector3& v);

	Vector3 operator-=(const Vector3& v);

	Vector3 operator*=(const Vector3& v);

	Vector3 operator*=(float scale);

	bool operator==(const Vector3& v);

	bool operator!=(const Vector3& v);

	Vector3 lerp(const Vector3& other, float alpha) const;

	float distance();

	void normalize();
};

ENGINE_NAMESPACE_END

#endif