#include "SkeletalMeshComponent.h"
#include "../Animation/Skeleton.h"
#include "../Animation/Animation.h"
#include "../Render/Shader.h"
#include "../GameObject/GameObject.h"
#include "../Render/Texture.h"
#include "../Render/VertexArray.h"
#include "../Common/Mesh.h"

ENGINE_NAMESPACE_START

SkeletalMeshComponent::SkeletalMeshComponent(GameObject* gameObject)
	: MeshComponent(gameObject, true)
	, _skeleton(nullptr)
{

}

void SkeletalMeshComponent::draw(class Shader* shader)
{
	if (_mesh)
	{
		// Set the world transform
		shader->setMatrixUniform("uWorldTransform", _gameObject->getWorldTransform());
		// Set the matrix palette
		shader->setMatrixUniforms("uMatrixPalette", &_palette.entry[0], MAX_SKELETON_BONES);
		// Set specular power
		shader->setFloatUniform("uSpecPower", _mesh->getSpecPower());
		// Set the active texture
		Texture* t = _mesh->getTexture(_textureIndex);
		if (t)
		{
			t->setActive();
		}
		// Set the mesh's vertex array as active
		VertexArray* va = _mesh->getVertexArray();
		va->setActive();
		// Draw
		glDrawElements(GL_TRIANGLES, va->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}
}

void SkeletalMeshComponent::update(float deltaTime)
{
	if (_animation && _skeleton)
	{
		_animTime += deltaTime * _animPlayRate;
		// Wrap around anim time if past duration
		while (_animTime > _animation->getDuration())
		{
			_animTime -= _animation->getDuration();
		}

		// Recompute matrix palette
		computeMatrixPalette();
	}
}

void SkeletalMeshComponent::setSkeleton(const Skeleton* sk)
{
	_skeleton = sk;
}

float SkeletalMeshComponent::playAnimation(const Animation* anim, float playRate)
{
	_animation = anim;
	_animTime = 0.0f;
	_animPlayRate = playRate;

	if (!_animation)
	{
		return 0.0f;
	}

	computeMatrixPalette();

	return _animation->getDuration();
}

void SkeletalMeshComponent::computeMatrixPalette()
{
	const std::vector<Matrix4>& globalInvBindPoses = _skeleton->getGlobalInvBindPose();
	std::vector<Matrix4> currentPoses;
	_animation->getGlobalPoseAtTime(currentPoses, _skeleton, _animTime);

	// Setup the palette for each bone
	for (size_t i = 0; i < _skeleton->getBonesCount(); i++)
	{
		// Global inverse bind pose matrix times current pose matrix
		_palette.entry[i] = currentPoses[i] * globalInvBindPoses[i];
	}
}

ENGINE_NAMESPACE_END