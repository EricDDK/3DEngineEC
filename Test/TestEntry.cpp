#include "TestEntry.h"

#include "TestLog.h"
#include "TestMath.h"
#include "TestMemoryPool.h"
#include "TestPlatform.h"
#include "TestTexture.h"

void testEntry()
{
	TestLog testLog; testLog.testLog();
	TestMath testMath; testMath.testMath();
	TestMemoryPool testMemory; testMemory.testMemoryPool();
	TestPlatform testPlatform; testPlatform.testPlatform();
	TestTexture testTexture; testTexture.testTexture();
}