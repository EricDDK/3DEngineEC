#include "Component.h"

ENGINE_NAMESPACE_START

Component::Component()
	:_order(0)
{

}

Component::~Component()
{

}

void Component::update(float deltaTime)
{

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