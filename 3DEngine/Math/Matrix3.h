#ifndef __MATH_MATRIX3_H__
#define __MATH_MATRIX3_H__

#include "../Common/Macro.h"
#include "Vector2.h"

ENGINE_NAMESPACE_START

class Matrix3
{
public:
	float mat[3][3];

	Matrix3();

	~Matrix3();

	Matrix3(const Matrix3& m);

	Matrix3(float m[3][3]);

	Matrix3 operator*(const Matrix3& rhs);

	Matrix3 operator*=(const Matrix3& rhs);

	const float *getShaderPtr() const;

	static Matrix3 createScale(float xScale, float yScale);

	static Matrix3 createScale(const Vector2& scale);

	static Matrix3 createScale(float scale);

	static Matrix3 createRotation(float theta);

	static Matrix3 createTranslation(const Vector2& trans);

	const static Matrix3 Identity;
};

ENGINE_NAMESPACE_END

#endif