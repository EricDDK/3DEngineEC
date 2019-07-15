#include "iostream"

#include "TestPlatform.cpp"

int main(int argc, char** argv)
{
	// test start
	{
		testPlatform();

	}

	std::cout << "test result : " << totalTest - totolError << "/" << totalTest << std::endl;
	std::cout << "pass percent : " << (float)(totalTest - totolError) / (float)totalTest * 100.0f << "%" << std::endl;
	return 1;
}