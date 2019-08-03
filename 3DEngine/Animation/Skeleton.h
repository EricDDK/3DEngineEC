#ifndef _ANIMATION_SKELETON_H__
#define _ANIMATION_SKELETON_H__

#include "../Common/Macro.h"
#include "BoneTransform.h"
#include "Bone.h"
#include <vector>

ENGINE_NAMESPACE_START

class Skeleton
{
public:

	bool load(const std::string& fileName);

	size_t getBonesCount() const;

	const Bone& getBone(size_t idx) const;

	const std::vector<Bone>& getBones() const;

	const std::vector<Matrix4>& getGlobalInvBindPose() const;

protected:

	// Computes the global inverse bind pose for each bone
	void computeGlobalInvBindPose();

private:

	std::vector<Bone> _bones;

	// The global inverse bind poses for each bone
	std::vector<Matrix4> _globalInvBindPoses;

};

ENGINE_NAMESPACE_END

#endif