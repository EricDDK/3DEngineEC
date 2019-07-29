#ifndef _COMPONENT_CAMERACOMPONENT_H__
#define _COMPONENT_CAMERACOMPONENT_H__

#include "../Common/Macro.h"
#include "Component.h"
#include "../Math/Matrix4.h"

ENGINE_NAMESPACE_START

class CameraComponent : public Component
{
public:

	CameraComponent(GameObject *gameObject, int order = 200);

	~CameraComponent();

	void setViewMatrix(const Matrix4& view);

};

ENGINE_NAMESPACE_END

#endif