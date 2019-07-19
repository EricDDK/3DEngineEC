#include "Matrix3.h"

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

static float m3Ident[3][3] = 
{
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f }
};

const Matrix3 Matrix3::Identity(m3Ident);

ENGINE_NAMESPACE_END