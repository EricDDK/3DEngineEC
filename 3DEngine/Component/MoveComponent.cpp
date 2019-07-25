#include "MoveComponent.h"
#include "../Math/Math.h"

ENGINE_NAMESPACE_START

MoveComponent::MoveComponent(GameObject *owner, int order)
	:Component(owner, order)
	, _angularSpeed(0.0f)
	, _forwardSpeed(0.0f)
	, _rightSpeed(0.0f)
{

}

MoveComponent::~MoveComponent()
{

}

void MoveComponent::update(float deltaTime)
{
	if (!math::nearZero(_angularSpeed))
	{
		Quaternion rotate = _owner->getRotation();
		float angle = _angularSpeed * deltaTime;
		Quaternion inc(Vector3::UnitZ, angle);
		rotate = Quaternion::concatenate(rotate, inc);
		_owner->setRotation(rotate);
	}

	if (!math::nearZero(_forwardSpeed) || !math::nearZero(_rightSpeed))
	{
		Vector3 pos = _owner->getPosition();
		pos += _owner->getForward() * _forwardSpeed * deltaTime;
		pos += _owner->getRight() * _rightSpeed * deltaTime;
		_owner->setPosition(pos);
	}
}

void MoveComponent::setAngularSpeed(float angularSpeed)
{
	_angularSpeed = angularSpeed;
}

float MoveComponent::getAngularSpeed() const
{
	return _angularSpeed;
}

void MoveComponent::setForwardSpeed(float forwardSpeend)
{
	_forwardSpeed = forwardSpeend;
}

float MoveComponent::getForwardSpeed() const
{
	return _forwardSpeed;
}

void MoveComponent::setRightSpeed(float rightSpeend)
{
	_rightSpeed = rightSpeend;
}

float MoveComponent::getRightSpeed() const
{
	return _rightSpeed;
}

ENGINE_NAMESPACE_END