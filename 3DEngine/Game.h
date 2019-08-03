#ifndef _GAME_H__
#define _GAME_H__

#include "Common/Macro.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <SDL/SDL_types.h>
#include <SDL/SDL_timer.h>
#include "Math/Math.h"

ENGINE_NAMESPACE_START

class GameObject;
class Render;
class UIScreen;
class Font;
class Animation;
class Skeleton;
class SpriteComponent;
class PlaneGameObject;

class Game
{
public:

	enum GameState
	{
		Gameplay,
		Paused,
		Quit
	};

	Game();

	~Game();

	bool init();

	void runLoop();

	void shutDown();

	void addGameObject(GameObject* gameObject);

	void removeGameObject(GameObject* gameObject);

	Render* getRender() const;

	const std::vector<class UIScreen*>& getUIStack();

	void pushUI(class UIScreen* screen);

	void setState(GameState state);

	GameState getState() const;

	Font* getFont(const std::string& fileName);

	void loadText(const std::string& fileName);

	const std::string& getText(const std::string& key);

	Skeleton* getSkeleton(const std::string& fileName);

	Animation* getAnimation(const std::string& fileName);

	void addPlane(PlaneGameObject* plane);

	void removePlane(PlaneGameObject* plane);

	std::vector<PlaneGameObject*> getPlanes();

private:

	void processInput();

	void handleKeyPress(int key);

	void updateGame();

	void generateOutput();

	void loadData();

	void unloadData();

	// All objects in game
	std::vector<GameObject*> _gameObjects;

	std::vector<UIScreen*> _UIStack;

	std::unordered_map<std::string, Font*> _fonts;

	std::unordered_map<std::string, Skeleton*> _skeletons;

	std::unordered_map<std::string, Animation*> _animations;

	std::unordered_map<std::string, std::string> _texts;

	std::vector<GameObject*> _pendingObjects;

	Render* _render;

	Uint32 _ticksCount;

	GameState _state;

	SpriteComponent* _croosHair;

	std::vector<PlaneGameObject*> _planes;

	SpriteComponent* _crossHair;

	bool _updateGameObjects;

};

ENGINE_NAMESPACE_END

#endif