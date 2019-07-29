#include "BoneTransform.h"

ENGINE_NAMESPACE_START

Matrix4 BoneTransform::toMatrix() const
{
	Matrix4 rotate = Matrix4::createQueternion(_rotateion);
	Matrix4 translation = Matrix4::createTranslation(_translation);

	return rotate * translation;
}

BoneTransform BoneTransform::Interpolate(const BoneTransform& a, const BoneTransform& b, float f)
{
	BoneTransform result;

	result._rotateion = Quaternion::slerp(a._rotateion, b._rotateion, f);
	result._translation = Vector3::lerp(a._translation, b._translation, f);

	return result;
}

ENGINE_NAMESPACE_END