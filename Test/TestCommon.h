#include "iostream"

#ifdef _MSC_VER
#ifdef _DEBUG
#define New   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#define CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#endif

// expect test
#define EXPECT(expect, actual) \
do {\
    if (expect != actual) {\
        fprintf(stderr, "%s:%d: \n", __FILE__, __LINE__);\
		totolError++;\
	}\
	totalTest++;\
}while(0)

// unexpect test
#define UNEXPEXT(unexpect, actual) \
do {\
    if (unexpect == actual) {\
        fprintf(stderr, "%s:%d: \n", __FILE__, __LINE__);\
		totolError++;\
	}\
	totalTest++;\
}while(0)

static int totolError = 0;
static int totalTest = 0;