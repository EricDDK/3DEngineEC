#ifndef __MATH_VECTOR3_H__
#define __MATH_VECTOR3_H__

#include "../Common/Macro.h"

ENGINE_NAMESPACE_START

class Quaternion;
class Matrix4;

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

	const float *getShaderPtr() const;

	Vector3 lerp(const Vector3& other, float alpha) const;

	float distance();

	void normalize();

	static Vector3 normalize(const Vector3& vec);

	static float dot(const Vector3& lhs, const Vector3& rhs);

	static Vector3 cross(const Vector3& lhs, const Vector3& rhs);

	static Vector3 transform(const Vector3& v, const Quaternion& q);

	static Vector3 transform(const Vector3& v, const Matrix4& m, float w = 1.0f);

	static const Vector3 Zero;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;

};

ENGINE_NAMESPACE_END

#endif