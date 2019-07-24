#ifndef _COMPONENT_COMPONENT_H__
#define _COMPONENT_COMPONENT_H__

#include "../Common/Macro.h"
#include "../GameObject/GameObject.h"

ENGINE_NAMESPACE_START

class Component
{
public:
	Component();

	Component(GameObject *owner, int order);

	virtual ~Component();

	virtual void update(float deltaTime);

	virtual void processInput(const unsigned char* keyState);

	virtual void onUpdateWorldTransform();

	void setOwner(GameObject *owner);

	GameObject *getOwner() const;

	void setOrder(int order);

	int getOrder() const;

protected:

	GameObject *_owner;

	int _order;
};

ENGINE_NAMESPACE_END

#endif