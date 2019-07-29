#include "Animation.h"
#include "Skeleton.h"
#include <fstream>
#include <sstream>
#include "rapidjson/include/rapidjson/document.h"
#include "../Common/Log.h"

ENGINE_NAMESPACE_START

bool Animation::load(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		log("File not found: Animation = %s", fileName.c_str());
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		log("Animation %s is not valid json", fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the metadata
	if (ver != 1)
	{
		log("Animation %s unknown format", fileName.c_str());
		return false;
	}

	const rapidjson::Value& sequence = doc["sequence"];
	if (!sequence.IsObject())
	{
		log("Animation %s doesn't have a sequence.", fileName.c_str());
		return false;
	}

	const rapidjson::Value& frames = sequence["frames"];
	const rapidjson::Value& length = sequence["length"];
	const rapidjson::Value& bonecount = sequence["bonecount"];

	if (!frames.IsUint() || !length.IsDouble() || !bonecount.IsUint())
	{
		log("Sequence %s has invalid frames, length, or bone count.", fileName.c_str());
		return false;
	}

	_framesCount = frames.GetUint();
	_duration = length.GetDouble();
	_bonesCount = bonecount.GetUint();
	_frameDuration = _duration / (_framesCount - 1);

	_tracks.resize(_bonesCount);

	const rapidjson::Value& tracks = sequence["tracks"];

	if (!tracks.IsArray())
	{
		log("Sequence %s missing a tracks array.", fileName.c_str());
		return false;
	}

	for (rapidjson::SizeType i = 0; i < tracks.Size(); i++)
	{
		if (!tracks[i].IsObject())
		{
			log("Animation %s: Track element %d is invalid.", fileName.c_str(), i);
			return false;
		}

		size_t boneIndex = tracks[i]["bone"].GetUint();

		const rapidjson::Value& transforms = tracks[i]["transforms"];
		if (!transforms.IsArray())
		{
			log("Animation %s: Track element %d is missing transforms.", fileName.c_str(), i);
			return false;
		}

		BoneTransform temp;

		if (transforms.Size() < _framesCount)
		{
			log("Animation %s: Track element %d has fewer frames than expected.", fileName.c_str(), i);
			return false;
		}

		for (rapidjson::SizeType j = 0; j < transforms.Size(); j++)
		{
			const rapidjson::Value& rot = transforms[j]["rot"];
			const rapidjson::Value& trans = transforms[j]["trans"];

			if (!rot.IsArray() || !trans.IsArray())
			{
				log("Skeleton %s: Bone %d is invalid.", fileName.c_str(), i);
				return false;
			}

			temp._rotateion.x = rot[0].GetDouble();
			temp._rotateion.y = rot[1].GetDouble();
			temp._rotateion.z = rot[2].GetDouble();
			temp._rotateion.w = rot[3].GetDouble();

			temp._translation.x = trans[0].GetDouble();
			temp._translation.y = trans[1].GetDouble();
			temp._translation.z = trans[2].GetDouble();

			_tracks[boneIndex].emplace_back(temp);
		}
	}

	return true;
}

size_t Animation::getBonesCount() const
{
	return _bonesCount;
}

size_t Animation::getFramesCount() const
{
	return _framesCount;
}

float Animation::getDuration() const
{
	return _duration;
}

float Animation::getFrameDuration() const
{
	return _frameDuration;
}

void Animation::getGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const Skeleton* inSkeleton, float inTime) const
{
	if (outPoses.size() != _bonesCount)
	{
		outPoses.resize(_bonesCount);
	}

	size_t frame = static_cast<size_t>(inTime / _frameDuration);
	size_t nextFrame = frame + 1;
	// Calculate fractional value between frame and next frame
	float pct = inTime / _frameDuration - frame;

	// Setup the pose for the root
	if (_tracks[0].size() > 0)
	{
		// calculate the Lerp value between the current frame's pose and the next frame
		// Interpolate between the current frame's pose and the next frame
		BoneTransform interp = BoneTransform::Interpolate(_tracks[0][frame], _tracks[0][nextFrame], pct);
		outPoses[0] = interp.toMatrix();
	}
	else
	{
		outPoses[0] = Matrix4::Identity;
	}

	const std::vector<Bone>& bones = inSkeleton->getBones();
	// Now setup the poses for the rest
	for (size_t bone = 1; bone < _bonesCount; bone++)
	{
		Matrix4 localMat; // (Defaults to identity)
		if (_tracks[bone].size() > 0)
		{
			// calculate the lerp BoneTransform between the current frame's pose and the next frame
			BoneTransform interp = BoneTransform::Interpolate(_tracks[bone][frame], _tracks[bone][nextFrame], pct);
			localMat = interp.toMatrix();
		}

		outPoses[bone] = localMat * outPoses[bones[bone].parent];
	}
}

ENGINE_NAMESPACE_END