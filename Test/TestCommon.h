#ifndef _TEST_COMMON_H__
#define _TEST_COMMON_H__

#include "iostream"

#ifdef _MSC_VER
#ifdef _DEBUG
#define New   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#define CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#endif

class TestCommon
{
public:
	TestCommon()
	{
		totalError = 0;
		totalTest = 0;
	}

	~TestCommon() = default;

	int totalError;
	int totalTest;
};

static TestCommon *s_test = new TestCommon();

// expect test
#define EXPECT(expect, actual) \
do {\
    if (expect != actual) {\
        fprintf(stderr, "%s:%d: \n", __FILE__, __LINE__);\
		s_test->totalError++;\
	}\
	s_test->totalTest++;\
}while(0)

// unexpect test
#define UNEXPEXT(unexpect, actual) \
do {\
    if (unexpect == actual) {\
        fprintf(stderr, "%s:%d: \n", __FILE__, __LINE__);\
		s_test->totalError++;\
	}\
	s_test->totalTest++;\
}while(0)

#endif