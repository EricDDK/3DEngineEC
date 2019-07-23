#ifndef _COMPONENT_COMPONENT_H__
#define _COMPONENT_COMPONENT_H__

#include "../Common/Macro.h"

ENGINE_NAMESPACE_START

class Component
{
public:
	Component();

	virtual ~Component();

	virtual void update(float deltaTime);

	void setOrder(int order);

	int getOrder() const;

protected:
	int _order;
};

ENGINE_NAMESPACE_END

#endif