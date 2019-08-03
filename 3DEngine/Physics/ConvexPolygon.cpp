#include "ConvexPolygon.h"
#include <cmath>
#include "../Math/MathCommon.h"

ENGINE_NAMESPACE_START

ConvexPolygon::ConvexPolygon(const std::vector<Vector2>& verts)
	: vertices(verts)
{

}

bool ConvexPolygon::contains(const Vector2& point) const
{
	float sum = 0.0f;
	Vector2 a, b;
	for (size_t i = 0; i < vertices.size() - 1; i++)
	{
		// From point to first vertex
		a = vertices[i] - point;
		a.normalize();
		// From point to second vertex
		b = vertices[i + 1] - point;
		b.normalize();
		// Add angle to sum
		sum += std::acosf(Vector2::dot(a, b));
	}
	// Have to add angle for last vertex and first vertex
	a = vertices.back() - point;
	a.normalize();
	b = vertices.front() - point;
	b.normalize();
	sum += std::acosf(Vector2::dot(a, b));
	// Return true if approximately 2pi
	return math::nearZero(sum - math::PI2);
}

ENGINE_NAMESPACE_END