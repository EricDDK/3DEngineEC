#ifndef _COMPONENT_BOXCOMPONENT_H__
#define _COMPONENT_BOXCOMPONENT_H__

#include "../Common/Macro.h"
#include "Component.h"
#include "../Physics/AABB.h"

ENGINE_NAMESPACE_START

class BoxComponent : public Component
{
public:

	BoxComponent(GameObject *gameObject, int order = 100);

	~BoxComponent();

	void onUpdateWorldTransform() override;

	void setObjectBox(const AABB& model);

	const AABB& getWorldBox() const;

	void setNeedRotate(bool b);
	
private:

	AABB _objectBox;

	AABB _worldBox;

	bool _needRotate;

};

ENGINE_NAMESPACE_END

#endif