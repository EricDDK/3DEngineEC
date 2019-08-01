#ifndef _LIGHT_DIRECTIONLIGHT_H__
#define _LIGHT_DIRECTIONLIGHT_H__

#include "../Common/Macro.h"
#include "../Math/Math.h"

ENGINE_NAMESPACE_START

class DirectionalLight
{
public:
	// Direction of light
	Vector3 direction;
	// Diffuse color
	Vector3 diffuseColor;
	// Specular color
	Vector3 specColor;
};

ENGINE_NAMESPACE_END

#endif