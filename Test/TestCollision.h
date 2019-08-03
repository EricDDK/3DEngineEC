#ifndef _TEST_COLLISION_H__
#define _TEST_COLLISION_H__

#include "TestCommon.h"
#include "Physics/AABB.h"

class TestCollision
{
public:

	void testCollision()
	{
		testAABB();
	}

private:

	void testAABB()
	{
		engine::AABB aabb(engine::Vector3(0.0f, 0.0f, 0.0f), engine::Vector3(1.0f, 1.0f, 1.0f));
		EXPECT(aabb.contain(engine::Vector3(0.5f, 0.5f, 0.5f)), true);
		aabb = engine::AABB(engine::Vector3(0.0f, 0.0f, 0.0f), engine::Vector3(1.0f, 1.0f, 1.0f));
		EXPECT(aabb.contain(engine::Vector3(1.5f, 0.5f, 0.5f)), false);
		aabb = engine::AABB(engine::Vector3(0.0f, 0.0f, 0.0f), engine::Vector3(1.0f, 1.0f, 1.0f));
		EXPECT(aabb.contain(engine::Vector3(1.1f, 0.5f, 0.5f)), false);
		aabb = engine::AABB(engine::Vector3(0.0f, 0.0f, 0.0f), engine::Vector3(1.0f, 1.0f, 1.0f));
		EXPECT(aabb.contain(engine::Vector3(1.0f, 1.0f, 1.0f)), true);
	}

};

#endif