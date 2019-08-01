#ifndef _COMPONENT_COMPONENT_H__
#define _COMPONENT_COMPONENT_H__

#include "../Common/Macro.h"
#include "../GameObject/GameObject.h"

ENGINE_NAMESPACE_START

class Component
{
public:
	Component();

	Component(GameObject *gameObject, int order = 100);

	virtual ~Component();

	virtual void update(float deltaTime);

	virtual void processInput(const unsigned char* keyState);

	virtual void onUpdateWorldTransform();

	void setgameObject(GameObject *gameObject);

	GameObject *getgameObject() const;

	void setOrder(int order);

	int getOrder() const;

protected:

	GameObject *_gameObject;

	int _order;
};

ENGINE_NAMESPACE_END

#endif