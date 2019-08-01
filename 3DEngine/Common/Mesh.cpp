#include "Mesh.h"
#include "../Render/Texture.h"
#include "../Render/Render.h"
#include "../Render/VertexArray.h"
#include <limits>
#include <fstream>
#include <sstream>
#include <rapidjson/include/rapidjson/document.h>
#include "../Common/Log.h"
#include <cmath>
#include<algorithm>

ENGINE_NAMESPACE_START

union Vertex
{
	float f;
	uint8_t b[4];
};

Mesh::Mesh()
	: _box(Vector3(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()), 
		Vector3(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity()))
	, _vertexArray(nullptr)
	, _radius(0.0f)
	, _specPower(100.0f)
{

}

Mesh::~Mesh()
{

}

bool Mesh::load(const std::string& fileName, Render *render)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		log("File not found: Mesh %s", fileName.c_str());
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
		log("Mesh %s is not valid json", fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the version
	if (ver != 1)
	{
		log("Mesh %s not version 1", fileName.c_str());
		return false;
	}

	_shaderName = doc["shader"].GetString();

	// Set the vertex layout/size based on the format in the file
	VertexArray::Layout layout = VertexArray::PosNormTex;
	size_t vertSize = 8;

	std::string vertexFormat = doc["vertexformat"].GetString();
	if (vertexFormat == "PosNormSkinTex")
	{
		layout = VertexArray::PosNormSkinTex;
		// This is the number of "Vertex" unions, which is 8 + 2 (for skinning)s
		vertSize = 10;
	}

	// Load textures
	const rapidjson::Value& textures = doc["textures"];
	if (!textures.IsArray() || textures.Size() < 1)
	{
		log("Mesh %s has no textures, there should be at least one", fileName.c_str());
		return false;
	}

	_specPower = static_cast<float>(doc["specularPower"].GetDouble());

	for (rapidjson::SizeType i = 0; i < textures.Size(); i++)
	{
		// Is this texture already loaded?
		std::string texName = textures[i].GetString();
		Texture* t = render->getTexture(texName);
		if (t == nullptr)
		{
			// Try loading the texture
			t = render->getTexture(texName);
			if (t == nullptr)
			{
				// If it's still null, just use the default texture
				t = render->getTexture("Assets/Default.png");
			}
		}
		_textures.emplace_back(t);
	}

	// Load in the vertices
	const rapidjson::Value& vertsJson = doc["vertices"];
	if (!vertsJson.IsArray() || vertsJson.Size() < 1)
	{
		log("Mesh %s has no vertices", fileName.c_str());
		return false;
	}

	std::vector<Vertex> vertices;
	vertices.reserve(vertsJson.Size() * vertSize);
	_radius = 0.0f;
	for (rapidjson::SizeType i = 0; i < vertsJson.Size(); i++)
	{
		// For now, just assume we have 8 elements
		const rapidjson::Value& vert = vertsJson[i];
		if (!vert.IsArray())
		{
			log("Unexpected vertex format for %s", fileName.c_str());
			return false;
		}

		Vector3 pos(vert[0].GetDouble(), vert[1].GetDouble(), vert[2].GetDouble());
		_radius = std::max(_radius, pos.lengthSq());
		_box.update(pos);

		if (layout == VertexArray::PosNormTex)
		{
			Vertex v;
			// Add the floats
			for (rapidjson::SizeType j = 0; j < vert.Size(); j++)
			{
				v.f = static_cast<float>(vert[j].GetDouble());
				vertices.emplace_back(v);
			}
		}
		else
		{
			Vertex v;
			// Add pos/normal
			for (rapidjson::SizeType j = 0; j < 6; j++)
			{
				v.f = static_cast<float>(vert[j].GetDouble());
				vertices.emplace_back(v);
			}

			// Add skin information
			for (rapidjson::SizeType j = 6; j < 14; j += 4)
			{
				v.b[0] = vert[j].GetUint();
				v.b[1] = vert[j + 1].GetUint();
				v.b[2] = vert[j + 2].GetUint();
				v.b[3] = vert[j + 3].GetUint();
				vertices.emplace_back(v);
			}

			// Add tex coords
			for (rapidjson::SizeType j = 14; j < vert.Size(); j++)
			{
				v.f = vert[j].GetDouble();
				vertices.emplace_back(v);
			}
		}
	}

	// We were computing length squared earlier
	_radius = std::sqrt(_radius);

	// Load in the indices
	const rapidjson::Value& indJson = doc["indices"];
	if (!indJson.IsArray() || indJson.Size() < 1)
	{
		log("Mesh %s has no indices", fileName.c_str());
		return false;
	}

	std::vector<unsigned int> indices;
	indices.reserve(indJson.Size() * 3);
	for (rapidjson::SizeType i = 0; i < indJson.Size(); i++)
	{
		const rapidjson::Value& ind = indJson[i];
		if (!ind.IsArray() || ind.Size() != 3)
		{
			log("Invalid indices for %s", fileName.c_str());
			return false;
		}

		indices.emplace_back(ind[0].GetUint());
		indices.emplace_back(ind[1].GetUint());
		indices.emplace_back(ind[2].GetUint());
	}

	// Now create a vertex array
	_vertexArray = new VertexArray(vertices.data(), static_cast<unsigned>(vertices.size()) / vertSize,
		layout, indices.data(), static_cast<unsigned>(indices.size()));
	return true;
}

void Mesh::unload()
{
	delete _vertexArray;
	_vertexArray = nullptr;
}

VertexArray* Mesh::getVertexArray()
{
	return _vertexArray;
}

Texture* Mesh::getTexture(size_t index)
{
	if (index < _textures.size())
	{
		return _textures[index];
	}
	else
	{
		return nullptr;
	}
}

const std::string& Mesh::getShaderName() const
{
	return _shaderName;
}

float Mesh::getRadius() const
{
	return _radius;
}

const AABB& Mesh::getBox() const
{
	return _box;
}

float Mesh::getSpecPower() const
{
	return _specPower;
}

ENGINE_NAMESPACE_END