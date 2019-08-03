#include "Sphere.h"

ENGINE_NAMESPACE_START

Sphere::Sphere(const Vector3 & cen, float rad)
	: center(cen)
	, radius(rad)
{

}

bool Sphere::contains(const Vector3 & point) const
{
	float d = (center - point).lengthSq();
	return d <= (radius * radius);
}

ENGINE_NAMESPACE_END