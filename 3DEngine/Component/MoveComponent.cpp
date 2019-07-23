#include "MoveComponent.h"

ENGINE_NAMESPACE_START

MoveComponent::MoveComponent()
{

}

MoveComponent::~MoveComponent()
{

}

void MoveComponent::update(float deltaTime)
{

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

ENGINE_NAMESPACE_END