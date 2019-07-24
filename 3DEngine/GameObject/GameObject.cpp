#include "GameObject.h"
#include "../Component/Component.h"

#include <algorithm>

ENGINE_NAMESPACE_START

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::update(float deltaTime)
{

}

void GameObject::updateComponents(float deltaTime)
{

}

void GameObject::processInput(const unsigned char* keyState)
{

}

void GameObject::gameObjectInput(const unsigned char* keyState)
{

}

void GameObject::setPosition(const Vector3& pos)
{
	_position = pos;
	_reComputerMat4 = true;
}

const Vector3& GameObject::getPosition() const
{
	return _position;
}

void GameObject::setRotation(const Quaternion& q)
{
	_rotation = q;
	_reComputerMat4 = true;
}

const Quaternion& GameObject::getRotation() const
{
	return _rotation;
}

void GameObject::setScale(float scale)
{
	_scale = scale;
	_reComputerMat4 = true;
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