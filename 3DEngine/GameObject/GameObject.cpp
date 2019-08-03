#include "GameObject.h"
#include "../Component/Component.h"

#include <algorithm>

ENGINE_NAMESPACE_START

GameObject::GameObject()
	:_state(Active)
	, _position(0.0f, 0.0f, 0.0f)
	, _rotation(Quaternion::Identity)
	, _worldTransform(Matrix4::Identity)
	, _scale(1.0f)
	, _reComputeMat4(true)
{
	// TODO
	// addActor
}

GameObject::~GameObject()
{
	// TODO
	// removeActor
	for (auto& c : _components)
	{
		delete c;
	}
}

void GameObject::update(float deltaTime)
{
	if (_state == Active)
	{
		computeWorldTransform();
		updateComponents(deltaTime);
		updateGameObject(deltaTime);
		computeWorldTransform();
	}
}

void GameObject::updateComponents(float deltaTime)
{

}

void GameObject::updateGameObject(float deltaTime)
{

}

void GameObject::processInput(const unsigned char* keyState)
{
	if (_state == Active)
	{
		for (auto& c : _components)
		{
			c->processInput(keyState);
		}
		gameObjectInput(keyState);
	}
}

void GameObject::gameObjectInput(const unsigned char* keyState)
{

}

void GameObject::setPosition(const Vector3& pos)
{
	_position = pos;
	_reComputeMat4 = true;
}

const Vector3& GameObject::getPosition() const
{
	return _position;
}

void GameObject::setRotation(const Quaternion& q)
{
	_rotation = q;
	_reComputeMat4 = true;
}

const Quaternion& GameObject::getRotation() const
{
	return _rotation;
}

void GameObject::setScale(float scale)
{
	_scale = scale;
	_reComputeMat4 = true;
}

float GameObject::getScale() const
{
	return _scale;
}

const Matrix4& GameObject::getWorldTransform() const
{
	return _worldTransform;
}

void GameObject::computeWorldTransform()
{
	if (_reComputeMat4)
	{
		// the calculate sequence is important and order must be this.
		_worldTransform = Matrix4::createScale(_scale);
		_worldTransform *= Matrix4::createQueternion(_rotation);
		_worldTransform *= Matrix4::createTranslation(_position);

		for (auto& c : _components)
		{
			c->onUpdateWorldTransform();
		}
		_reComputeMat4 = false;
	}
}

void GameObject::setState(State state)
{
	_state = state;
}

GameObject::State GameObject::getState() const
{
	return _state;
}

Vector3 GameObject::getForward() const
{
	return Vector3::transform(Vector3::UnitX, _rotation);
}

Vector3 GameObject::getRight() const
{
	return Vector3::transform(Vector3::UnitY, _rotation);
}

void GameObject::addComponent(Component *component)
{
	int order = component->getOrder();
	auto iter = _components.begin();
	for (; iter != _components.end(); ++iter)
	{
		if (order < (*iter)->getOrder())
		{
			break;
		}
	}
	_components.insert(iter, component);
}

void GameObject::removeComponent(Component *component)
{
	auto iter = std::find(_components.begin(), _components.end(), component);
	if (iter != _components.end())
	{
		_components.erase(iter);
	}
}

ENGINE_NAMESPACE_END