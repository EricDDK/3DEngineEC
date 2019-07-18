#ifndef __MATH_VECTOR2_H__
#define __MATH_VECTOR2_H__

#include "../Common/Macro.h"

ENGINE_NAMESPACE_START

class Vector2
{
public:

	float x;

	float y;

	Vector2();

	~Vector2();

	Vector2(float tX, float tY);

	Vector2(const Vector2& v);

	Vector2 operator=(const Vector2& v);

	void set(float tX, float tY);

	void set(const Vector2& v);

	Vector2 operator+(const Vector2& v) const;

	Vector2 operator-(const Vector2& v) const;

	float operator*(const Vector2& v) const;

	Vector2 operator*(float scale) const;

	Vector2 operator+=(const Vector2& v);

	Vector2 operator-=(const Vector2& v);

	Vector2 operator*=(const Vector2& v);

	Vector2 operator*=(float scale);

	bool operator==(const Vector2& v);

	bool operator!=(const Vector2& v);

	Vector2 lerp(const Vector2& other, float alpha) const;

	float distance();

	void normalize();
};

ENGINE_NAMESPACE_END

#endif