#ifndef _TEST_SHADER_H__
#define _TEST_SHADER_H__

#include "TestCommon.h"
#include "Render/Shader.h"

class TestShader
{
public:
	void testShader()
	{
		engine::Shader shader;
		// openGL must init before call shader test.
		/*bool isLoad = shader.load("Test.vs", "Test.fs");
		EXPECT(isLoad, true);*/

	}
};

#endif