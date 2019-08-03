#ifndef _RENDER_RENDER_H__
#define _RENDER_RENDER_H__

#include "../Common/Macro.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL/SDL.h>
#include "../Math/Math.h"
#include "../Light/DirectionalLight.h"
#include "../Render/VertexArray.h"

ENGINE_NAMESPACE_START

class SpriteComponent;
class Game;
class Mesh;
class MeshComponent;
class SkeletalMeshComponent;
class Texture;
class Shader;

class Render
{
public:

	Render(Game* game);

	~Render();

	bool init(float screenWidth, float screenHeight);

	void shutDown();

	void unloadData();

	void draw();

	void addSprite(SpriteComponent *sprite);

	void removeSprite(SpriteComponent *sprite);

	void addMeshComp(MeshComponent* mesh);

	void removeMeshComp(MeshComponent* mesh);

	Texture* getTexture(const std::string& fileName);

	Mesh* getMesh(const std::string& fileName);

	void setViewMatrix(const Matrix4& view);

	void setAmbientLight(const Vector3& ambient);

	DirectionalLight& getDirectionalLight();

	// Given a screen space point, unprojects it into world space,
	// based on the current 3D view/projection matrices
	// Expected ranges:
	// x = [-screenWidth/2, +screenWidth/2]
	// y = [-screenHeight/2, +screenHeight/2]
	// z = [0, 1) -- 0 is closer to camera, 1 is further
	Vector3 unProject(const Vector3& screenPoint);

	void getScreenDirection(Vector3& outStart, Vector3& outDir) const;

	float getScreenWidth() const;

	float getScreenHeight() const;

private:

	bool loadShaders();

	void createSpriteVerts();

	void setLightUniforms(Shader* shader);

	std::unordered_map<std::string, Texture*> _textures;

	std::unordered_map<std::string, Mesh*> _meshes;

	std::vector<SpriteComponent*> _sprites;

	std::vector<MeshComponent*> _meshComps;

	std::vector<SkeletalMeshComponent*> _skeletalMeshes;

	Game* _game;

	Shader* _spriteShader;

	VertexArray* _spriteVerts;

	Shader* _meshShader;

	Shader* _skinnedShader;

	Matrix4 _view;

	Matrix4 _projection;

	float _screenWidth;

	float _screenHeight;

	// Light
	Vector3 _ambientLight;

	DirectionalLight _dirLight;

	// Windows
	SDL_Window* _window;

	SDL_GLContext _context;

};

ENGINE_NAMESPACE_END

#endif