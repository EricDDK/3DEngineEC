#ifndef _TEST_ANI_OS_H__
#define _TEST_ANI_OS_H__

#include "TestCommon.h"
#include "Animation/Skeleton.h"

class TestAniOS
{
public:

	void testAniOS()
	{
		testSkeleton();
	}

private:

	void testSkeleton()
	{
		engine::Skeleton skeleton;
		skeleton.load("");
	}

};

#endif