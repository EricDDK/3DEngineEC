#include "Game.h"
#include "GameObject/GameObject.h"
#include "Render/Render.h"
#include "GameObject\PlaneGameObject.h"
#include "UI/UIScreen.h"
#include "UI/Font.h"
#include "Animation/Animation.h"
#include "Animation/Skeleton.h"
#include "Component/SpriteComponent.h"
#include "GameObject/PlaneGameObject.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Common/Log.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <rapidjson/include/rapidjson/document.h>

ENGINE_NAMESPACE_START

Game::Game()
	: _state(Gameplay)
	, _updateGameObjects(false)
{

}

Game::~Game()
{

}

bool Game::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// create the render
	_render = new Render(this);
	if (!_render->init(1024.0f, 768.0f))
	{
		log("Failed to initialize renderer");
		delete _render;
		_render = nullptr;
		return false;
	}

	if (TTF_Init() != 0)
	{
		log("Failed to initialize SDL_ttf");
		return false;
	}

	loadData();

	_ticksCount = SDL_GetTicks();

	return true;
}

void Game::runLoop()
{
	while (_state != Quit)
	{
		processInput();
		updateGame();
		generateOutput();
	}
}

void Game::shutDown()
{
	unloadData();
	TTF_Quit();
	if (_render)
	{
		_render->shutDown();
	}
	SDL_Quit();
}

void Game::addGameObject(GameObject* gameObject)
{
	// If we're updating objects, need to add to pending
	if (_updateGameObjects)
	{
		_pendingObjects.emplace_back(gameObject);
	}
	else
	{
		_gameObjects.emplace_back(gameObject);
	}
}

void Game::removeGameObject(GameObject* gameObject)
{
	// Is it in pending actors?
	auto iter = std::find(_pendingObjects.begin(), _pendingObjects.end(), gameObject);
	if (iter != _pendingObjects.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, _pendingObjects.end() - 1);
		_pendingObjects.pop_back();
	}

	// Is it in actors?
	iter = std::find(_gameObjects.begin(), _gameObjects.end(), gameObject);
	if (iter != _gameObjects.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, _gameObjects.end() - 1);
		_gameObjects.pop_back();
	}
}

Render* Game::getRender() const
{
	return _render;
}

const std::vector<class UIScreen*>& Game::getUIStack()
{
	return _UIStack;
}

void Game::pushUI(class UIScreen* screen)
{
	_UIStack.emplace_back(screen);
}

void Game::setState(GameState state)
{
	_state = state;
}

Game::GameState Game::getState() const
{
	return _state;
}

Font* Game::getFont(const std::string& fileName)
{
	auto iter = _fonts.find(fileName);
	if (iter != _fonts.end())
	{
		return iter->second;
	}
	else
	{
		Font* font = new Font(this);
		if (font->load(fileName))
		{
			_fonts.emplace(fileName, font);
		}
		else
		{
			font->unload();
			delete font;
			font = nullptr;
		}
		return font;
	}
}

void Game::loadText(const std::string& fileName)
{
	// Clear the existing map, if already loaded
	_texts.clear();
	// Try to open the file
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		SDL_Log("Text file %s not found", fileName.c_str());
		return;
	}
	// Read the entire file to a string stream
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	// Open this file in rapidJSON
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);
	if (!doc.IsObject())
	{
		SDL_Log("Text file %s is not valid JSON", fileName.c_str());
		return;
	}
	// Parse the text map
	const rapidjson::Value& actions = doc["TextMap"];
	for (rapidjson::Value::ConstMemberIterator itr = actions.MemberBegin();
		itr != actions.MemberEnd(); ++itr)
	{
		if (itr->name.IsString() && itr->value.IsString())
		{
			_texts.emplace(itr->name.GetString(),
				itr->value.GetString());
		}
	}
}

const std::string& Game::getText(const std::string& key)
{
	static std::string errorMsg("**KEY NOT FOUND**");
	// Find this text in the map, if it exists
	auto iter = _texts.find(key);
	if (iter != _texts.end())
	{
		return iter->second;
	}
	else
	{
		return errorMsg;
	}
}

Skeleton* Game::getSkeleton(const std::string& fileName)
{
	auto iter = _skeletons.find(fileName);
	if (iter != _skeletons.end())
	{
		return iter->second;
	}
	else
	{
		Skeleton* sk = new Skeleton();
		if (sk->load(fileName))
		{
			_skeletons.emplace(fileName, sk);
		}
		else
		{
			delete sk;
			sk = nullptr;
		}
		return sk;
	}
}

Animation* Game::getAnimation(const std::string& fileName)
{
	auto iter = _animations.find(fileName);
	if (iter != _animations.end())
	{
		return iter->second;
	}
	else
	{
		Animation* anim = new Animation();
		if (anim->load(fileName))
		{
			_animations.emplace(fileName, anim);
		}
		else
		{
			delete anim;
			anim = nullptr;
		}
		return anim;
	}
}

void Game::addPlane(PlaneGameObject* plane)
{
	_planes.emplace_back(plane);
}

void Game::removePlane(PlaneGameObject* plane)
{
	auto iter = std::find(_planes.begin(), _planes.end(), plane);
	_planes.erase(iter);
}

std::vector<PlaneGameObject*> Game::getPlanes()
{
	return _planes;
}

void Game::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_state = Quit;
			break;
			// This fires when a key's initially pressed
		case SDL_KEYDOWN:
			if (!event.key.repeat)
			{
				if (_state == Gameplay)
				{
					handleKeyPress(event.key.keysym.sym);
				}
				else if (!_UIStack.empty())
				{
					_UIStack.back()->
						handleKeyPress(event.key.keysym.sym);
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (_state == Gameplay)
			{
				handleKeyPress(event.button.button);
			}
			else if (!_UIStack.empty())
			{
				_UIStack.back()->
					handleKeyPress(event.button.button);
			}
			break;
		default:
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (_state == Gameplay)
	{
		for (auto actor : _gameObjects)
		{
			if (actor->getState() == GameObject::Active)
			{
				actor->processInput(state);
			}
		}
	}
	else if (!_UIStack.empty())
	{
		_UIStack.back()->processInput(state);
	}
}

void Game::handleKeyPress(int key)
{
	switch (key)
	{
	case SDLK_ESCAPE:
		// Create pause menu
		_state = Quit;
		break;
	}
}

void Game::updateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), _ticksCount + 16));

	float deltaTime = (SDL_GetTicks() - _ticksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	_ticksCount = SDL_GetTicks();

	if (_state == Gameplay)
	{
		_updateGameObjects = true;
		for (auto go : _gameObjects)
		{
			go->update(deltaTime);
		}
		_updateGameObjects = false;

		for (auto pg : _pendingObjects)
		{
			pg->computeWorldTransform();
			_gameObjects.emplace_back(pg);
		}
		_pendingObjects.clear();

		std::vector<GameObject*> deadObjects;
		for (auto go : _gameObjects)
		{
			if (go->getState() == GameObject::Dead)
			{
				deadObjects.emplace_back(go);
			}
		}

		for (auto dgo : deadObjects)
		{
			delete dgo;
		}
	}

	// Delete any UIScreens that are closed
	auto iter = _UIStack.begin();
	while (iter != _UIStack.end())
	{
		if ((*iter)->getState() == UIScreen::Closing)
		{
			delete *iter;
			iter = _UIStack.erase(iter);
		}
		else
		{
			++iter;
		}
	}

}

void Game::generateOutput()
{
	_render->draw();
}

void Game::loadData()
{
	loadText("Assets/English.gptext");

	GameObject* go = nullptr;
	Quaternion q;

	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			go = new PlaneGameObject(this);
			go->setPosition(Vector3(start + i * size, start + j * size, -100.0f));
		}
	}

	// Left/right walls
	q = Quaternion(Vector3::UnitX, math::PiOVER2);
	for (int i = 0; i < 10; i++)
	{
		go = new PlaneGameObject(this);
		go->setPosition(Vector3(start + i * size, start - size, 0.0f));
		go->setRotation(q);

		go = new PlaneGameObject(this);
		go->setPosition(Vector3(start + i * size, -start + size, 0.0f));
		go->setRotation(q);
	}

	q = Quaternion::concatenate(q, Quaternion(Vector3::UnitZ, math::PiOVER2));
	// Forward/back walls
	for (int i = 0; i < 10; i++)
	{
		go = new PlaneGameObject(this);
		go->setPosition(Vector3(start - size, start + i * size, 0.0f));
		go->setRotation(q);

		go = new PlaneGameObject(this);
		go->setPosition(Vector3(-start + size, start + i * size, 0.0f));
		go->setRotation(q);
	}

	// Setup lights
	_render->setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = _render->getDirectionalLight();
	dir.direction = Vector3(0.0f, -0.707f, -0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// Enable relative mouse mode for camera look
	SDL_SetRelativeMouseMode(SDL_TRUE);
	// Make an initial call to get relative to clear out
	SDL_GetRelativeMouseState(nullptr, nullptr);

	// Different camera actors
	//mFollowActor = new FollowActor(this);

	//// Create target actors
	//go = new TargetActor(this);
	//go->SetPosition(Vector3(1450.0f, 0.0f, 100.0f));
	//go = new TargetActor(this);
	//go->SetPosition(Vector3(1450.0f, 0.0f, 400.0f));
	//go = new TargetActor(this);
	//go->SetPosition(Vector3(1450.0f, -500.0f, 200.0f));
	//go = new TargetActor(this);
	//go->SetPosition(Vector3(1450.0f, 500.0f, 200.0f));
	//go = new TargetActor(this);
	//go->SetPosition(Vector3(0.0f, -1450.0f, 200.0f));
	//go->SetRotation(Quaternion(Vector3::UnitZ, math::PiOVER2));
	//go = new TargetActor(this);
	//go->SetPosition(Vector3(0.0f, 1450.0f, 200.0f));
	//go->SetRotation(Quaternion(Vector3::UnitZ, -math::PiOVER2));
}

void Game::unloadData()
{
	while (!_gameObjects.empty())
	{
		delete _gameObjects.back();
	}

	while (!_UIStack.empty())
	{
		delete _UIStack.back();
		_UIStack.pop_back();
	}

	if (_render)
	{
		_render->unloadData();
	}

	for (auto f : _fonts)
	{
		f.second->unload();
		delete f.second;
	}

	for (auto s : _skeletons)
	{
		delete s.second;
	}

	for (auto a : _animations)
	{
		delete a.second;
	}
}

ENGINE_NAMESPACE_END