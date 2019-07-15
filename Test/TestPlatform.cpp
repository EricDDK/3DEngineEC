#include "Common/3DEngine.h"
#include "TestCommon.h"

 static void testPlatform()
{
	 auto platform = engine::TARGET_PLATFORM;
	 UNEXPEXT(platform, engine::Platform::None);

}
