#include "Matrix3.h"

#include <cmath>
#include <memory.h>

ENGINE_NAMESPACE_START

Matrix3::Matrix3()
{
	*this = Matrix3::Identity;
}

Matrix3::~Matrix3()
{

}

Matrix3::Matrix3(const Matrix3& m)
{
	memcpy(mat, m.mat, 9 * sizeof(float));
}

Matrix3::Matrix3(float m[3][3])
{
	memcpy(mat, m, 9 * sizeof(float));
}

Matrix3 Matrix3::operator*(const Matrix3& rhs)
{
	Matrix3 result;
	// row 0
	result.mat[0][0] =
		this->mat[0][0] * rhs.mat[0][0] +
		this->mat[0][1] * rhs.mat[1][0] +
		this->mat[0][2] * rhs.mat[2][0];

	result.mat[0][1] =
		this->mat[0][0] * rhs.mat[0][1] +
		this->mat[0][1] * rhs.mat[1][1] +
		this->mat[0][2] * rhs.mat[2][1];

	result.mat[0][2] =
		this->mat[0][0] * rhs.mat[0][2] +
		this->mat[0][1] * rhs.mat[1][2] +
		this->mat[0][2] * rhs.mat[2][2];

	// row 1
	result.mat[1][0] =
		this->mat[1][0] * rhs.mat[0][0] +
		this->mat[1][1] * rhs.mat[1][0] +
		this->mat[1][2] * rhs.mat[2][0];

	result.mat[1][1] =
		this->mat[1][0] * rhs.mat[0][1] +
		this->mat[1][1] * rhs.mat[1][1] +
		this->mat[1][2] * rhs.mat[2][1];

	result.mat[1][2] =
		this->mat[1][0] * rhs.mat[0][2] +
		this->mat[1][1] * rhs.mat[1][2] +
		this->mat[1][2] * rhs.mat[2][2];

	// row 2
	result.mat[2][0] =
		this->mat[2][0] * rhs.mat[0][0] +
		this->mat[2][1] * rhs.mat[1][0] +
		this->mat[2][2] * rhs.mat[2][0];

	result.mat[2][1] =
		this->mat[2][0] * rhs.mat[0][1] +
		this->mat[2][1] * rhs.mat[1][1] +
		this->mat[2][2] * rhs.mat[2][1];

	result.mat[2][2] =
		this->mat[2][0] * rhs.mat[0][2] +
		this->mat[2][1] * rhs.mat[1][2] +
		this->mat[2][2] * rhs.mat[2][2];
	return result;
}

Matrix3 Matrix3::operator*=(const Matrix3& rhs)
{
	*this = *this * rhs;
	return *this;
}

Matrix3 Matrix3::createScale(float xScale, float yScale)
{
	Matrix3 result;
	result.mat[0][0] = xScale;
	result.mat[1][1] = yScale;
	return result;
}

Matrix3 Matrix3::createScale(const Vector2 & scale)
{
	return createScale(scale.x, scale.y);
}

Matrix3 Matrix3::createScale(float scale)
{
	return createScale(scale, scale);
}

Matrix3 Matrix3::createRotation(float theta)
{
	Matrix3 result;
	result.mat[0][0] = std::cos(theta);
	result.mat[0][1] = std::sin(theta);
	result.mat[1][0] = -std::sin(theta);
	result.mat[1][1] = std::cos(theta);
	return result;
}

Matrix3 Matrix3::createTranslation(const Vector2 & trans)
{
	Matrix3 result;
	result.mat[2][0] = trans.x;
	result.mat[2][1] = trans.y;
	return result;
}

static float m3Ident[3][3] = 
{
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f }
};

const Matrix3 Matrix3::Identity(m3Ident);

ENGINE_NAMESPACE_END