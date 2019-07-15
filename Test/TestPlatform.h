#ifndef _TEST_PLATFORMCONFIG_H__
#define _TEST_PLATFORMCONFIG_H__

#include "TestCommon.h"
#include "Common/3DEngine.h"

class TestPlatform
{
public:
	void testPlatform()
	{
		auto platform = engine::TARGET_PLATFORM;
		UNEXPEXT(platform, engine::Platform::None);

	}
};

#endif