#include "Component.h"

ENGINE_NAMESPACE_START

Component::Component()
	:_order(0)
{

}

Component::Component(GameObject *owner, int order = 0)
	:_owner(owner)
	,_order(order)
{
	_owner->addComponent(this);
}

Component::~Component()
{
	_owner->removeComponent(this);
}

void Component::update(float deltaTime)
{

}

void Component::processInput(const unsigned char* keyState)
{

}

void Component::setOwner(GameObject *owner)
{
	if (_owner)
	{
		_owner->removeComponent(this);
	}
	_owner = owner;
	owner->addComponent(this);
}

GameObject *Component::getOwner() const
{
	return _owner;
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