#include "Matrix4.h"
#include "Quaternion.h"

#include <cmath>
#include <memory.h>

#include "VectorUtil.h"

ENGINE_NAMESPACE_START

Matrix4::Matrix4()
{
	*this = Matrix4::Identity;
}

Matrix4::~Matrix4()
{

}

Matrix4::Matrix4(const Matrix4 & m)
{
	memcpy(this->mat, m.mat, 16 * sizeof(float));
}

Matrix4::Matrix4(float m[4][4])
{
	memcpy(this->mat, m, 16 * sizeof(float));
}

Matrix4 Matrix4::operator*(const Matrix4 & rhs)
{
	Matrix4 result;
	// row 0
	result.mat[0][0] =
		this->mat[0][0] * rhs.mat[0][0] +
		this->mat[0][1] * rhs.mat[1][0] +
		this->mat[0][2] * rhs.mat[2][0] +
		this->mat[0][3] * rhs.mat[3][0];

	result.mat[0][1] =
		this->mat[0][0] * rhs.mat[0][1] +
		this->mat[0][1] * rhs.mat[1][1] +
		this->mat[0][2] * rhs.mat[2][1] +
		this->mat[0][3] * rhs.mat[3][1];

	result.mat[0][2] =
		this->mat[0][0] * rhs.mat[0][2] +
		this->mat[0][1] * rhs.mat[1][2] +
		this->mat[0][2] * rhs.mat[2][2] +
		this->mat[0][3] * rhs.mat[3][2];

	result.mat[0][3] =
		this->mat[0][0] * rhs.mat[0][3] +
		this->mat[0][1] * rhs.mat[1][3] +
		this->mat[0][2] * rhs.mat[2][3] +
		this->mat[0][3] * rhs.mat[3][3];

	// row 1
	result.mat[1][0] =
		this->mat[1][0] * rhs.mat[0][0] +
		this->mat[1][1] * rhs.mat[1][0] +
		this->mat[1][2] * rhs.mat[2][0] +
		this->mat[1][3] * rhs.mat[3][0];

	result.mat[1][1] =
		this->mat[1][0] * rhs.mat[0][1] +
		this->mat[1][1] * rhs.mat[1][1] +
		this->mat[1][2] * rhs.mat[2][1] +
		this->mat[1][3] * rhs.mat[3][1];

	result.mat[1][2] =
		this->mat[1][0] * rhs.mat[0][2] +
		this->mat[1][1] * rhs.mat[1][2] +
		this->mat[1][2] * rhs.mat[2][2] +
		this->mat[1][3] * rhs.mat[3][2];

	result.mat[1][3] =
		this->mat[1][0] * rhs.mat[0][3] +
		this->mat[1][1] * rhs.mat[1][3] +
		this->mat[1][2] * rhs.mat[2][3] +
		this->mat[1][3] * rhs.mat[3][3];

	// row 2
	result.mat[2][0] =
		this->mat[2][0] * rhs.mat[0][0] +
		this->mat[2][1] * rhs.mat[1][0] +
		this->mat[2][2] * rhs.mat[2][0] +
		this->mat[2][3] * rhs.mat[3][0];

	result.mat[2][1] =
		this->mat[2][0] * rhs.mat[0][1] +
		this->mat[2][1] * rhs.mat[1][1] +
		this->mat[2][2] * rhs.mat[2][1] +
		this->mat[2][3] * rhs.mat[3][1];

	result.mat[2][2] =
		this->mat[2][0] * rhs.mat[0][2] +
		this->mat[2][1] * rhs.mat[1][2] +
		this->mat[2][2] * rhs.mat[2][2] +
		this->mat[2][3] * rhs.mat[3][2];

	result.mat[2][3] =
		this->mat[2][0] * rhs.mat[0][3] +
		this->mat[2][1] * rhs.mat[1][3] +
		this->mat[2][2] * rhs.mat[2][3] +
		this->mat[2][3] * rhs.mat[3][3];

	// row 3
	result.mat[3][0] =
		this->mat[3][0] * rhs.mat[0][0] +
		this->mat[3][1] * rhs.mat[1][0] +
		this->mat[3][2] * rhs.mat[2][0] +
		this->mat[3][3] * rhs.mat[3][0];

	result.mat[3][1] =
		this->mat[3][0] * rhs.mat[0][1] +
		this->mat[3][1] * rhs.mat[1][1] +
		this->mat[3][2] * rhs.mat[2][1] +
		this->mat[3][3] * rhs.mat[3][1];

	result.mat[3][2] =
		this->mat[3][0] * rhs.mat[0][2] +
		this->mat[3][1] * rhs.mat[1][2] +
		this->mat[3][2] * rhs.mat[2][2] +
		this->mat[3][3] * rhs.mat[3][2];

	result.mat[3][3] =
		this->mat[3][0] * rhs.mat[0][3] +
		this->mat[3][1] * rhs.mat[1][3] +
		this->mat[3][2] * rhs.mat[2][3] +
		this->mat[3][3] * rhs.mat[3][3];
	return result;
}

Matrix4 Matrix4::operator*=(const Matrix4 & rhs)
{
	*this = *this * rhs;
	return *this;
}

void Matrix4::invert()
{
	float tmp[12];
	float src[16];
	float dst[16];
	float det;

	// Transpose matrix
	// row 1 to col 1
	src[0] = mat[0][0];
	src[4] = mat[0][1];
	src[8] = mat[0][2];
	src[12] = mat[0][3];

	// row 2 to col 2
	src[1] = mat[1][0];
	src[5] = mat[1][1];
	src[9] = mat[1][2];
	src[13] = mat[1][3];

	// row 3 to col 3
	src[2] = mat[2][0];
	src[6] = mat[2][1];
	src[10] = mat[2][2];
	src[14] = mat[2][3];

	// row 4 to col 4
	src[3] = mat[3][0];
	src[7] = mat[3][1];
	src[11] = mat[3][2];
	src[15] = mat[3][3];

	// Calculate cofactors
	tmp[0] = src[10] * src[15];
	tmp[1] = src[11] * src[14];
	tmp[2] = src[9] * src[15];
	tmp[3] = src[11] * src[13];
	tmp[4] = src[9] * src[14];
	tmp[5] = src[10] * src[13];
	tmp[6] = src[8] * src[15];
	tmp[7] = src[11] * src[12];
	tmp[8] = src[8] * src[14];
	tmp[9] = src[10] * src[12];
	tmp[10] = src[8] * src[13];
	tmp[11] = src[9] * src[12];

	dst[0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
	dst[0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
	dst[1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
	dst[1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
	dst[2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
	dst[2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
	dst[3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
	dst[3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
	dst[4] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
	dst[4] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
	dst[5] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
	dst[5] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
	dst[6] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
	dst[6] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
	dst[7] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
	dst[7] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];

	tmp[0] = src[2] * src[7];
	tmp[1] = src[3] * src[6];
	tmp[2] = src[1] * src[7];
	tmp[3] = src[3] * src[5];
	tmp[4] = src[1] * src[6];
	tmp[5] = src[2] * src[5];
	tmp[6] = src[0] * src[7];
	tmp[7] = src[3] * src[4];
	tmp[8] = src[0] * src[6];
	tmp[9] = src[2] * src[4];
	tmp[10] = src[0] * src[5];
	tmp[11] = src[1] * src[4];

	dst[8] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
	dst[8] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
	dst[9] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
	dst[9] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
	dst[10] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
	dst[10] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
	dst[11] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
	dst[11] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
	dst[12] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
	dst[12] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
	dst[13] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
	dst[13] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
	dst[14] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
	dst[14] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
	dst[15] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
	dst[15] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];

	// Calculate determinant
	det = src[0] * dst[0] + src[1] * dst[1] + src[2] * dst[2] + src[3] * dst[3];

	// Inverse of matrix is divided by determinant
	det = 1 / det;
	for (int j = 0; j < 16; j++)
	{
		dst[j] *= det;
	}

	// Set it back
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat[i][j] = dst[i * 4 + j];
		}
	}
}

Matrix4 Matrix4::createScale(float xScale, float yScale, float zScale)
{
	Matrix4 result;
	result.mat[0][0] = xScale;
	result.mat[1][1] = yScale;
	result.mat[2][2] = zScale;
	return result;
}

Matrix4 Matrix4::createScale(const Vector3& scale)
{
	return createScale(scale.x, scale.y, scale.z);
}

Matrix4 Matrix4::createScale(float scale)
{
	return createScale(scale, scale, scale);
}

Matrix4 Matrix4::createQueternion(const Quaternion& q)
{
	float mat[4][4];

	mat[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
	mat[0][1] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
	mat[0][2] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
	mat[0][3] = 0.0f;

	mat[1][0] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
	mat[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
	mat[1][2] = 2.0f * q.y * q.z + 2.0f * q.w * q.x;
	mat[1][3] = 0.0f;

	mat[2][0] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
	mat[2][1] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
	mat[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
	mat[2][3] = 0.0f;

	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;

	return Matrix4(mat);
}

Matrix4 Matrix4::createRotationX(float theta)
{
	Matrix4 result;
	result.mat[1][1] = std::cos(theta);
	result.mat[1][2] = std::sin(theta);
	result.mat[2][1] = -std::sin(theta);
	result.mat[2][2] = std::cos(theta);
	return result;
}

Matrix4 Matrix4::createRotationY(float theta)
{
	Matrix4 result;
	result.mat[0][0] = std::cos(theta);
	result.mat[0][2] = -std::sin(theta);
	result.mat[2][0] = std::sin(theta);
	result.mat[2][2] = std::cos(theta);
	return result;
}

Matrix4 Matrix4::createRotationZ(float theta)
{
	Matrix4 result;
	result.mat[0][0] = std::cos(theta);
	result.mat[0][1] = std::sin(theta);
	result.mat[1][0] = -std::sin(theta);
	result.mat[1][1] = std::cos(theta);
	return result;
}

Matrix4 Matrix4::createTranslation(const Vector3& trans)
{
	Matrix4 result;
	result.mat[3][0] = trans.x;
	result.mat[3][1] = trans.y;
	result.mat[3][2] = trans.z;
	return result;
}

Matrix4 Matrix4::createLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	Vector3 zaxis = Vector3::normalize(target - eye);
	Vector3 xaxis = Vector3::normalize(VectorUtil::cross(up, zaxis));
	Vector3 yaxis = Vector3::normalize(VectorUtil::cross(zaxis, xaxis));
	Vector3 trans;
	trans.x = -VectorUtil::dot(xaxis, eye);
	trans.y = -VectorUtil::dot(yaxis, eye);
	trans.z = -VectorUtil::dot(zaxis, eye);

	float temp[4][4] =
	{
		{ xaxis.x, yaxis.x, zaxis.x, 0.0f },
		{ xaxis.y, yaxis.y, zaxis.y, 0.0f },
		{ xaxis.z, yaxis.z, zaxis.z, 0.0f },
		{ trans.x, trans.y, trans.z, 1.0f }
	};
	return Matrix4(temp);
}

Matrix4 Matrix4::createOrtho(float width, float height, float near, float far)
{
	float temp[4][4] =
	{
		{ 2.0f / width, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 2.0f / height, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f / (far - near), 0.0f },
		{ 0.0f, 0.0f, near / (near - far), 1.0f }
	};
	return Matrix4(temp);
}

Matrix4 Matrix4::createPerspective(float fovY, float width, float height, float near, float far)
{
	float yScale = 1 / std::tan(fovY / 2.0f);
	float xScale = yScale * height / width;
	float temp[4][4] =
	{
		{ xScale, 0.0f, 0.0f, 0.0f },
		{ 0.0f, yScale, 0.0f, 0.0f },
		{ 0.0f, 0.0f, far / (far - near), 1.0f },
		{ 0.0f, 0.0f, -near * far / (far - near), 0.0f }
	};
	return Matrix4(temp);
}

float m4Ident[4][4] = {
	{ 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f }
};

const Matrix4 Matrix4::Identity(m4Ident);

ENGINE_NAMESPACE_END
