#include "iostream"

#include "TestCommon.h"
#include "TestLog.h"
#include "TestMath.h"
#include "TestMemoryPool.h"
#include "TestPlatform.h"

int main(int argc, char** argv)
{
	// test start
	{
		TestLog testLog; testLog.testLog();
		TestMath testMath; testMath.testMath();
		TestMemoryPool testMemory; testMemory.testMemoryPool();
		TestPlatform testPlatform; testPlatform.testPlatform();
	}

	std::cout << "test result : " << s_test->totalTest - s_test->totalError << "/" << s_test->totalTest << std::endl;
	std::cout << "pass percent : " << (float)(s_test->totalTest - s_test->totalError) / (float)s_test->totalTest * 100.0f << "%" << std::endl;

#ifdef _MSC_VER
	system("pause");
#else

#endif
	return 1;
}