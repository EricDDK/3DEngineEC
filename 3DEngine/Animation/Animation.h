#ifndef _ANIMATION_ANIMATION_H__
#define _ANIMATION_ANIMATION_H__

#include "../Common/Macro.h"
#include "BoneTransform.h"
#include <string>
#include <vector>

ENGINE_NAMESPACE_START

class Skeleton;

class Animation
{
public:

	bool load(const std::string& fileName);

	size_t getBonesCount() const;

	size_t getFramesCount() const;

	float getDuration() const;

	float getFrameDuration() const;

	// Fills the provided vector with the global (current) pose matrices for each
	// bone at the specified time in the animation. It is expected that the time
	// is >= 0.0f and <= _duration
	void getGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const Skeleton* inSkeleton, float inTime) const;
	
private:

	size_t _bonesCount;

	size_t _framesCount;

	float _duration;

	float _frameDuration;

	// Transform information for each frame on the track
	// Each index in the outer vector is a bone, inner vector
	// is a frame
	std::vector<std::vector<BoneTransform>> _tracks;

};

ENGINE_NAMESPACE_END

#endif