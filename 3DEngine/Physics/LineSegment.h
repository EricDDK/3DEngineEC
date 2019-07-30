#ifndef _PHYSICS_LINESEGMENT_H__
#define _PHYSICS_LINESEGMENT_H__

#include "../Common/Macro.h"
#include "../Math/Math.h"

ENGINE_NAMESPACE_START

class LineSegment
{
public:

	Vector3 start;

	Vector3 end;

	LineSegment() = delete;

	LineSegment(const Vector3& start, const Vector3& end);

	~LineSegment();

	// Get point along segment where 0 <= t <= 1
	// like lerp
	Vector3 pointOnSegment(float t) const;

	// Get minimum distance squared between point and line segment
	float minDistSq(const Vector3& point) const;

	// Get minimum distance squared between two line segments
	static float minDistSq(const LineSegment& s1, const LineSegment& s2);

};

ENGINE_NAMESPACE_END

#endif