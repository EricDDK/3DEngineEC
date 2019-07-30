#include "AABB.h"
#include <cmath>
#include <array>

ENGINE_NAMESPACE_START

AABB::AABB(const Vector3& vMin, const Vector3& vMax)
	:min(vMin)
	,max(vMax)
{

}

AABB::~AABB()
{

}

void AABB::update(const Vector3& point)
{
	min.x = std::fmin(min.x, point.x);
	min.y = std::fmin(min.y, point.y);
	min.z = std::fmin(min.z, point.z);

	max.x = std::fmax(max.x, point.x);
	max.y = std::fmax(max.y, point.y);
	max.z = std::fmax(max.z, point.z);
}

void AABB::rotate(const Quaternion& q)
{
	std::array<Vector3, 8> points;
	points[0] = min;
	// Permutations with 2 min and 1 max
	points[1] = Vector3(max.x, min.y, min.z);
	points[2] = Vector3(min.x, max.y, min.z);
	points[3] = Vector3(min.x, min.y, max.z);
	// Permutations with 2 max and 1 min
	points[4] = Vector3(min.x, max.y, max.z);
	points[5] = Vector3(max.x, min.y, max.z);
	points[6] = Vector3(max.x, max.y, min.z);
	points[7] = max;

	Vector3 p = Vector3::transform(points[0], q);
	min = p;
	max = p;
	for (unsigned int i = 1; i < 8; ++i)
	{
		p = Vector3::transform(points[i], q);
		update(p);
	}
}

bool AABB::contain(const Vector3& point)
{
	bool isOut = point.x < min.x
		|| point.y < min.y
		|| point.z < min.z
		|| point.x > max.x
		|| point.y > max.y
		|| point.z > max.z;
	return !isOut;
}

ENGINE_NAMESPACE_END