#include "Render.h"
#include "../Game.h"
#include "../Component/SpriteComponent.h"
#include "../Component/MeshComponent.h"
#include "../Render/Texture.h"
#include "../Common/Mesh.h"
#include "../Render/Shader.h"
#include <GL/glew.h>
#include "../Common/Log.h"
#include "../UI/UIScreen.h"
#include "../Component/SkeletalMeshComponent.h"
#include "../Light/DirectionalLight.h"

ENGINE_NAMESPACE_START

Render::Render(Game* game)
	: _game(game)
	, _spriteShader(nullptr)
	, _meshShader(nullptr)
	, _skinnedShader(nullptr)
{

}

Render::~Render()
{

}

bool Render::init(float screenWidth, float screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	// Set OpenGL attributes
	// Use the core OpenGL profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// Specify version 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	_window = SDL_CreateWindow("3DEngineEEE Game", 100, 100,
		static_cast<int>(_screenWidth), static_cast<int>(_screenHeight), SDL_WINDOW_OPENGL);
	if (!_window)
	{
		log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// Create an OpenGL context
	_context = SDL_GL_CreateContext(_window);

	// Initialize GLFW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		log("Failed to initialize GLEW.");
		return false;
	}


	// On some platforms, GLFW will emit a benign error code,
	// so clear it
	glGetError();

	// Make sure we can create/compile shaders
	if (!loadShaders())
	{
		log("Failed to load shaders.");
		return false;
	}

	// Create quad for drawing sprites
	createSpriteVerts();

	return true;
}

void Render::shutDown()
{
	delete _spriteVerts;
	_spriteShader->unload();
	delete _spriteShader;
	_meshShader->unload();
	delete _meshShader;
	SDL_GL_DeleteContext(_context);
	SDL_DestroyWindow(_window);
}

void Render::unloadData()
{
	for (auto i : _textures)
	{
		i.second->unload();
		delete i.second;
	}
	_textures.clear();

	for (auto i : _meshes)
	{
		i.second->unload();
		delete i.second;
	}
	_meshes.clear();
}

void Render::draw()
{
	// Set the clear color to light grey
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw mesh components
	// Enable depth buffering/disable alpha blend
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	// Set the mesh shader active
	_meshShader->setActive();
	// Update view-projection matrix
	_meshShader->setMatrixUniform("uViewProj", _view * _projection);
	// Update lighting uniforms
	setLightUniforms(_meshShader);
	for (auto mc : _meshComps)
	{
		if (mc->getVisible())
		{
			mc->draw(_meshShader);
		}
	}

	// draw any skinned meshes now
	_skinnedShader->setActive();
	// Update view-projection matrix
	_skinnedShader->setMatrixUniform("uViewProj", _view * _projection);
	// Update lighting uniforms
	setLightUniforms(_skinnedShader);
	for (auto sk : _skeletalMeshes)
	{
		if (sk->getVisible())
		{
			sk->draw(_skinnedShader);
		}
	}

	// draw all sprite components
	// Disable depth buffering
	glDisable(GL_DEPTH_TEST);
	// Enable alpha blending on the color buffer
	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// Set shader/vao as active
	_spriteShader->setActive();
	_spriteVerts->setActive();
	for (auto sprite : _sprites)
	{
		if (sprite->isVisible())
		{
			sprite->draw(_spriteShader);
		}
	}

	// draw any UI screens
	for (auto ui : _game->getUIStack())
	{
		ui->draw(_spriteShader);
	}

	// Swap the buffers
	SDL_GL_SwapWindow(_window);
}

void Render::addSprite(SpriteComponent *sprite)
{
	int order = sprite->getOrder();
	auto iter = _sprites.begin();
	for (; iter != _sprites.end(); ++iter)
	{
		if (order < (*iter)->getOrder())
			break;
	}
	_sprites.insert(iter, sprite);
}

void Render::removeSprite(SpriteComponent *sprite)
{
	auto iter = std::find(_sprites.begin(), _sprites.end(), sprite);
	_sprites.erase(iter);
}

void Render::addMeshComp(MeshComponent* mesh)
{
	if (mesh->getIsSkeletal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(mesh);
		_meshComps.emplace_back(sk);
	}
	else
	{
		_meshComps.emplace_back(mesh);
	}
}

void Render::removeMeshComp(MeshComponent* mesh)
{
	if (mesh->getIsSkeletal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(mesh);
		auto iter = std::find(_meshComps.begin(), _meshComps.end(), sk);
		_meshComps.erase(iter);
	}
	else
	{
		auto iter = std::find(_meshComps.begin(), _meshComps.end(), mesh);
		_meshComps.erase(iter);
	}
}

Texture* Render::getTexture(const std::string& fileName)
{
	Texture* tex = nullptr;
	auto iter = _textures.find(fileName);
	if (iter != _textures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->load(fileName))
		{
			_textures.emplace(fileName, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

Mesh* Render::getMesh(const std::string& fileName)
{
	Mesh* m = nullptr;
	auto iter = _meshes.find(fileName);
	if (iter != _meshes.end())
	{
		m = iter->second;
	}
	else
	{
		m = new Mesh();
		if (m->load(fileName, this))
		{
			_meshes.emplace(fileName, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}
	return m;
}

void Render::setViewMatrix(const Matrix4& view)
{
	_view = view;
}

void Render::setAmbientLight(const Vector3& ambient)
{
	_ambientLight = ambient;
}

DirectionalLight& Render::getDirectionalLight()
{
	return _dirLight;
}

Vector3 Render::unProject(const Vector3& screenPoint)
{
	// ERROR
	return Vector3::Zero;
}

void Render::getScreenDirection(Vector3& outStart, Vector3& outDir) const
{
	// TODO
	// DEPERACATED
}

float Render::getScreenWidth() const
{
	return _screenWidth;
}

float Render::getScreenHeight() const
{
	return _screenHeight;
}

bool Render::loadShaders()
{
	// Create sprite shader
	_spriteShader = new Shader();
	if (!_spriteShader->load("../Shaders/Sprite.vert", "../Shaders/Sprite.frag"))
	{
		return false;
	}

	_spriteShader->setActive();
	// Set the view-projection matrix
	Matrix4 viewProj = Matrix4::createSimpleViewProj(_screenWidth, _screenHeight);
	_spriteShader->setMatrixUniform("uViewProj", viewProj);

	// Create basic mesh shader
	_meshShader = new Shader();
	if (!_meshShader->load("../Shaders/Phong.vert", "../Shaders/Phong.frag"))
	{
		return false;
	}

	_meshShader->setActive();
	// Set the view-projection matrix
	_view = Matrix4::createLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	_projection = Matrix4::createPerspective(math::toRadians(70.0f), _screenWidth, _screenHeight, 10.0f, 10000.0f);
	_meshShader->setMatrixUniform("uViewProj", _view * _projection);

	// Create skinned shader
	_skinnedShader = new Shader();
	if (!_skinnedShader->load("../Shaders/Skinned.vert", "../Shaders/Phong.frag"))
	{
		return false;
	}

	_skinnedShader->setActive();
	_skinnedShader->setMatrixUniform("uViewProj", _view * _projection);

	return true;
}

void Render::createSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	_spriteVerts = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);
}

void Render::setLightUniforms(Shader* shader)
{
	// Camera position is from inverted view
	Matrix4 invView = _view;
	invView.invert();
	shader->setVectorUniform("uCameraPos", invView.getTranslation());
	// Ambient light
	shader->setVectorUniform("uAmbientLight", _ambientLight);
	// Directional light
	shader->setVectorUniform("uDirLight.mDirection", _dirLight.direction);
	shader->setVectorUniform("uDirLight.mDiffuseColor", _dirLight.diffuseColor);
	shader->setVectorUniform("uDirLight.mSpecColor", _dirLight.specColor);
}

ENGINE_NAMESPACE_END