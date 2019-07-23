#include "TestCommon.h"



TestCommon *TestCommon::s_test = nullptr;

TestCommon *TestCommon::getInstance()
{
	if (s_test == nullptr) {
		s_test = new TestCommon;
	}
	return s_test;
}