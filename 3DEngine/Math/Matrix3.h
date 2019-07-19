#ifndef __MATH_VECTOR2_H__
#define __MATH_VECTOR2_H__

#include "../Common/Macro.h"

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

	const static Matrix3 Identity;
};

ENGINE_NAMESPACE_END

#endif