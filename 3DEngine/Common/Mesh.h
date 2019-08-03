#ifndef _COMMON_MESH_H__
#define _COMMON_MESH_H__

#include "../Common/Macro.h"
#include <vector>
#include <string>
#include "../Physics/AABB.h"

ENGINE_NAMESPACE_START

class Render;
class VertexArray;
class Texture;

class Mesh
{
public:

	Mesh();

	~Mesh();

	bool load(const std::string& fileName, Render *render);

	void unload();

	VertexArray* getVertexArray();

	Texture* getTexture(size_t index);

	const std::string& getShaderName() const;

	// Get object space bounding sphere radius
	float getRadius() const;

	const AABB& getBox() const;

	// Get specular power of mesh
	float getSpecPower() const;

private:

	AABB _box;

	// Textures associated with this mesh
	std::vector<class Texture*> _textures;

	VertexArray* _vertexArray;

	std::string _shaderName;

	float _radius;

	// Specular power of surface (jing mian fan she)
	float _specPower;

};

ENGINE_NAMESPACE_END

#endif