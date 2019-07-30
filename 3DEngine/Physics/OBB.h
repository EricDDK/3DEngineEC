#ifndef _PHYSICS_OBB_H__
#define _PHYSICS_OBB_H__

#include "../Common/Macro.h"
#include "../Math/Math.h"

ENGINE_NAMESPACE_START

class OBB
{
public:

	Vector3 center;

	Quaternion rotation;

	Vector3 extents;

};

ENGINE_NAMESPACE_END

#endif