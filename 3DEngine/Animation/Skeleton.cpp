#include "Skeleton.h"
#include <fstream>
#include <sstream>
#include "rapidjson/include/rapidjson/document.h"
#include "../Common/Log.h"

ENGINE_NAMESPACE_START

bool Skeleton::load(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		log("File not found: Skeleton %s", fileName.c_str());
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
		log("Skeleton %s is not valid json", fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the metadata
	if (ver != 1)
	{
		log("Skeleton %s unknown format", fileName.c_str());
		return false;
	}

	const rapidjson::Value& bonecount = doc["bonecount"];
	if (!bonecount.IsUint())
	{
		log("Skeleton %s doesn't have a bone count.", fileName.c_str());
		return false;
	}

	size_t count = bonecount.GetUint();

#define MAX_SKELETON_BONES 96
	if (count > MAX_SKELETON_BONES)
	{
		log("Skeleton %s exceeds maximum bone count.", fileName.c_str());
		return false;
	}

	_bones.reserve(count);

	const rapidjson::Value& bones = doc["bones"];
	if (!bones.IsArray())
	{
		log("Skeleton %s doesn't have a bone array?", fileName.c_str());
		return false;
	}

	if (bones.Size() != count)
	{
		log("Skeleton %s has a mismatch between the bone count and number of bones", fileName.c_str());
		return false;
	}

	Bone temp;

	for (rapidjson::SizeType i = 0; i < count; i++)
	{
		if (!bones[i].IsObject())
		{
			log("Skeleton %s: Bone %d is invalid.", fileName.c_str(), i);
			return false;
		}

		const rapidjson::Value& name = bones[i]["name"];
		temp.name = name.GetString();

		const rapidjson::Value& parent = bones[i]["parent"];
		temp.parent = parent.GetInt();

		const rapidjson::Value& bindpose = bones[i]["bindpose"];
		if (!bindpose.IsObject())
		{
			log("Skeleton %s: Bone %d is invalid.", fileName.c_str(), i);
			return false;
		}

		const rapidjson::Value& rot = bindpose["rot"];
		const rapidjson::Value& trans = bindpose["trans"];

		if (!rot.IsArray() || !trans.IsArray())
		{
			log("Skeleton %s: Bone %d is invalid.", fileName.c_str(), i);
			return false;
		}

		temp.localBindPose._rotateion.x = rot[0].GetDouble();
		temp.localBindPose._rotateion.y = rot[1].GetDouble();
		temp.localBindPose._rotateion.z = rot[2].GetDouble();
		temp.localBindPose._rotateion.w = rot[3].GetDouble();

		temp.localBindPose._translation.x = trans[0].GetDouble();
		temp.localBindPose._translation.y = trans[1].GetDouble();
		temp.localBindPose._translation.z = trans[2].GetDouble();

		_bones.emplace_back(temp);
	}

	// Now that we have the bones
	computeGlobalInvBindPose();

	return true;
}

size_t Skeleton::getBonesCount() const
{
	return _bones.size();
}

const Bone& Skeleton::getBone(size_t idx) const
{
	EC_ASSERT(_bones.empty());
	return _bones[idx];
}

const std::vector<Bone>& Skeleton::getBones() const
{
	return _bones;
}

const std::vector<Matrix4>& Skeleton::getGlobalInvBindPose() const
{
	return _globalInvBindPoses;
}

void Skeleton::computeGlobalInvBindPose()
{
	size_t n = _bones.size();
	_globalInvBindPoses.resize(n);

	// Step 1: Compute global bind pose for each bone
	_globalInvBindPoses[0] = _bones[0].localBindPose.toMatrix();
	Matrix4 localMat;
	for (size_t i = 1; i < n; ++i)
	{
		localMat = _bones[i].localBindPose.toMatrix();
		_globalInvBindPoses[i] = localMat * _globalInvBindPoses[_bones[i].parent];
	}

	// Step 2: Invert
	for (size_t i = 0; i < n; i++)
	{
		_globalInvBindPoses[i].invert();
	}
}

ENGINE_NAMESPACE_END