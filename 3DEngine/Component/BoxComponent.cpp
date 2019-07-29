#include "BoxComponent.h"

ENGINE_NAMESPACE_START

BoxComponent::BoxComponent(GameObject *gameObject, int order)
	: Component(gameObject, order)
	, _objectBox(Vector3::Zero, Vector3::Zero)
	, _worldBox(Vector3::Zero, Vector3::Zero)
	, _needRotate(true)
{
	// TODO
	// addBox
}

BoxComponent::~BoxComponent()
{
	// TODO

}

void BoxComponent::onUpdateWorldTransform()
{
	_worldBox = _objectBox;
	// Scale
	_worldBox.min *= _gameObject->getScale();
	_worldBox.max *= _gameObject->getScale();
	// Rotate
	if (_needRotate)
	{
		_worldBox.rotate(_gameObject->getRotation());
	}
	// Translate
	_worldBox.min += _gameObject->getPosition();
	_worldBox.max += _gameObject->getPosition();
}

void BoxComponent::setObjectBox(const AABB& model)
{
	_objectBox = model;
}

const AABB& BoxComponent::getWorldBox() const
{
	return _worldBox;
}

void BoxComponent::setNeedRotate(bool b)
{
	_needRotate = b;
}

ENGINE_NAMESPACE_END