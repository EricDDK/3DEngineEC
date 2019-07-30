#ifndef _PHYSICS_CONVEXPOLYGON_H__
#define _PHYSICS_CONVEXPOLYGON_H__

#include "../Common/Macro.h"
#include "../Math/Math.h"
#include <vector>

ENGINE_NAMESPACE_START

class ConvexPolygon
{
public:

	std::vector<Vector2> vertices;

	ConvexPolygon(const std::vector<Vector2>& verts);

	bool contains(const Vector2& point) const;

};

ENGINE_NAMESPACE_END

#endif