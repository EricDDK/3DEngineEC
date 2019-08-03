#include "iostream"

#include "TestEntry.h"

int main(int argc, char** argv)
{
	// test start
	{
		testEntry();
	}

	auto totalTest = TestCommon::getInstance()->totalTest;
	auto totalError = TestCommon::getInstance()->totalError;
	std::cout << "test result : " << totalTest - totalError << "/" << totalTest << std::endl;
	std::cout << "pass percent : " << (float)(totalTest - totalError) / (float)totalTest * 100.0f << "%" << std::endl;

#ifdef _MSC_VER
	system("pause");
#else

#endif
	return 1;
}