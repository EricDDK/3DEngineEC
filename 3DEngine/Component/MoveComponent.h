#ifndef _COMPONENT_MOVECOMPONENT_H__
#define _COMPONENT_MOVECOMPONENT_H__

#include "../Common/Macro.h"
#include "Component.h"

ENGINE_NAMESPACE_START

class MoveComponent : public Component
{
public:
	MoveComponent(GameObject *owner, int order);

	~MoveComponent();

	void update(float deltaTime);

	void setAngularSpeed(float angularSpeed);

	float getAngularSpeed() const;

	void setForwardSpeed(float forwardSpeend);

	float getForwardSpeed() const;

	void setRightSpeed(float rightSpeend);

	float getRightSpeed() const;

protected:

	float _angularSpeed;

	float _forwardSpeed;

	float _rightSpeed;

};

ENGINE_NAMESPACE_END

#endif