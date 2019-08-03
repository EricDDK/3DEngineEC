#ifndef _ANIMATION_BONE_H__
#define _ANIMATION_BONE_H__

#include "../Common/Macro.h"
#include "BoneTransform.h"
#include <string>

ENGINE_NAMESPACE_START

// also can be called joint
class Bone
{
public:

	BoneTransform localBindPose;

	std::string name;

	int parent;

};

ENGINE_NAMESPACE_END

#endif