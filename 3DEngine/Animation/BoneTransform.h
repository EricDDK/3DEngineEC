#ifndef _ANIMATION_BONETRANSFORM_H__
#define _ANIMATION_BONETRANSFORM_H__

#include "../Common/Macro.h"
#include "../Math/Math.h"

ENGINE_NAMESPACE_START

class BoneTransform
{
public:

	Quaternion _rotateion;

	Vector3 _translation;

	Matrix4 toMatrix() const;

	static BoneTransform Interpolate(const BoneTransform& a, const BoneTransform& b, float f);

};

ENGINE_NAMESPACE_END

#endif