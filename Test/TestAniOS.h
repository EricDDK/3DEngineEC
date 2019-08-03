#ifndef _TEST_ANI_OS_H__
#define _TEST_ANI_OS_H__

#include "TestCommon.h"
#include "Animation/Skeleton.h"
#include "Animation/Animation.h"

class TestAniOS
{
public:

	void testAniOS()
	{
		testSkeleton();
		testAnimation();
	}

private:

	void testSkeleton()
	{
		engine::Skeleton skeleton;
		skeleton.load("");
	}

	void testAnimation()
	{
		engine::Animation animation;
		animation.load("");
	}

};

#endif