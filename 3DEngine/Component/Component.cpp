#include "Component.h"

ENGINE_NAMESPACE_START

Component::Component()
	:_order(0)
{

}

Component::Component(GameObject *gameObject, int order)
	:_gameObject(gameObject)
	,_order(order)
{
	_gameObject->addComponent(this);
}

Component::~Component()
{
	_gameObject->removeComponent(this);
}

void Component::update(float deltaTime)
{

}

void Component::processInput(const unsigned char* keyState)
{

}

void Component::onUpdateWorldTransform()
{

}

void Component::setgameObject(GameObject *gameObject)
{
	if (_gameObject)
	{
		_gameObject->removeComponent(this);
	}
	_gameObject = gameObject;
	gameObject->addComponent(this);
}

GameObject *Component::getgameObject() const
{
	return _gameObject;
}

void Component::setOrder(int order)
{
	_order = order;
}

int Component::getOrder() const
{
	return _order;
}

ENGINE_NAMESPACE_END