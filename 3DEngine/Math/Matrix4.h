#ifndef __MATH_MATRIX4_H__
#define __MATH_MATRIX4_H__

#include "../Common/Macro.h"
#include "Vector3.h"

ENGINE_NAMESPACE_START

class Quaternion;

class Matrix4
{
public:
	float mat[4][4];

	Matrix4();

	~Matrix4();

	Matrix4(const Matrix4& m);

	Matrix4(float m[4][4]);

	Matrix4 operator*(const Matrix4& rhs);

	Matrix4 operator*=(const Matrix4& rhs);

	void invert();

	static Matrix4 createScale(float xScale, float yScale, float zScale);

	static Matrix4 createScale(const Vector3& scale);

	static Matrix4 createScale(float scale);

	static Matrix4 createQueternion(const Quaternion& q);

	static Matrix4 createRotationX(float theta);

	static Matrix4 createRotationY(float theta);

	static Matrix4 createRotationZ(float theta);

	static Matrix4 createTranslation(const Vector3& trans);

	static Matrix4 createLookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

	static Matrix4 createOrtho(float width, float height, float near, float far);

	static Matrix4 createPerspective(float fovY, float width, float height, float near, float far);

	static const Matrix4 Identity;
};

ENGINE_NAMESPACE_END

#endif