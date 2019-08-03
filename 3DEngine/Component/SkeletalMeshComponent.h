#ifndef _COMPONENT_SKELETALCOMPONENT_H__
#define _COMPONENT_SKELETALCOMPONENT_H__

#include "../Common/Macro.h"
#include "MeshComponent.h"

ENGINE_NAMESPACE_START

class Skeleton;
class Shader;
class GameObject;
class Animation;

#define MAX_SKELETON_BONES 96

struct MatrixPalette
{
	Matrix4 entry[MAX_SKELETON_BONES];
};

class SkeletalMeshComponent : public MeshComponent
{
public:

	SkeletalMeshComponent(GameObject* gameObject);

	// Draw this mesh component
	void draw(Shader* shader) override;

	void update(float deltaTime) override;

	// Setters
	void setSkeleton(const Skeleton* sk);

	// Play an animation. Returns the length of the animation
	float playAnimation(const Animation* anim, float playRate = 1.0f);

protected:

	void computeMatrixPalette();

	MatrixPalette _palette;

	const Skeleton* _skeleton;

	const Animation* _animation;

	float _animPlayRate;

	float _animTime;

};

ENGINE_NAMESPACE_END

#endif