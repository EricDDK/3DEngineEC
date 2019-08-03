#ifndef _GAMEOBJECT_GAMEOBJECT_H__
#define _GAMEOBJECT_GAMEOBJECT_H__

#include "../Common/Macro.h"

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix3.h"
#include "../Math/Matrix4.h"
#include "../Math/Quaternion.h"

#include <vector>

ENGINE_NAMESPACE_START

class Component;
class Game;

class GameObject
{
public:
	enum State
	{
		Dead,
		Active,
		Pause,
	};

	GameObject(Game* game);

	virtual ~GameObject();

	void update(float deltaTime);

	void updateComponents(float deltaTime);

	virtual void updateGameObject(float deltaTime);

	// callded from Game
	void processInput(const unsigned char* keyState);

	virtual void gameObjectInput(const unsigned char* keyState);

	void setPosition(const Vector3& pos);

	const Vector3& getPosition() const;

	void setRotation(const Quaternion& q);

	const Quaternion& getRotation() const;

	void setScale(float scale);

	float getScale() const;

	const Matrix4& getWorldTransform() const;

	void computeWorldTransform();

	void setState(State state);

	State getState() const;

	Vector3 getForward() const;

	Vector3 getRight() const;

	void addComponent(Component *component);

	void removeComponent(Component *component);

protected:

	Game* _game;
	
	State _state;

	Vector3 _position;

	Quaternion _rotation;

	Matrix4 _worldTransform;

	float _scale;

	bool _reComputeMat4;

	std::vector<Component *> _components;

};

ENGINE_NAMESPACE_END

#endif