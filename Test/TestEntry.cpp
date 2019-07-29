#include "TestEntry.h"

#include "TestAniOS.h"
#include "TestCollision.h"
#include "TestLog.h"
#include "TestMath.h"
#include "TestMemoryPool.h"
#include "TestPlatform.h"
#include "TestShader.h"
#include "TestTexture.h"

void testEntry()
{
	TestAniOS testAniOS;
	testAniOS.testAniOS();

	TestCollision testCollision;
	testCollision.testCollision();

	TestLog testLog; 
	testLog.testLog();

	TestMath testMath; 
	testMath.testMath();

	TestMemoryPool testMemory; 
	testMemory.testMemoryPool();

	TestPlatform testPlatform; 
	testPlatform.testPlatform();

	TestShader testShader; 
	testShader.testShader();

	TestTexture testTexture; 
	testTexture.testTexture();

}