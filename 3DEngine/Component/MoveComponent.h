#ifndef _COMPONENT_MOVECOMPONENT_H__
#define _COMPONENT_MOVECOMPONENT_H__

#include "../Common/Macro.h"

ENGINE_NAMESPACE_START

class MoveComponent
{
public:
	MoveComponent();

	~MoveComponent();

	void update(float deltaTime);

	void setAngularSpeed(float angularSpeed);

	float getAngularSpeed() const;

	void setForwardSpeed(float forwardSpeend);

	float getForwardSpeed() const;

protected:

	float _angularSpeed;

	float _forwardSpeed;

};

ENGINE_NAMESPACE_END

#endif