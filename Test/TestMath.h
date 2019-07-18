#ifndef _TEST_MATH_H__
#define _TEST_MATH_H__

#include "TestCommon.h"

#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/VectorUtil.h"

class TestMath
{
public:
	void testMath()
	{
		testVec2();
		testVec3();

		testVectorUtil();
	}

private:
	void testVec2()
	{
		engine::Vector2 v2;
		EXPECT(v2.x, 0.0f);
		EXPECT(v2.y, 0.0f);
		engine::Vector2 v(1.0f, 0.5f);
		EXPECT(v.x, 1.0f);
		EXPECT(v.y, 0.5f);
		engine::Vector2 v1(v);
		EXPECT(v1.x, 1.0f);
		EXPECT(v1.y, 0.5f);
		v1 = v2;
		EXPECT(v1.x, 0.0f);
		EXPECT(v1.y, 0.0f);
		auto d = v.distance();
		v.normalize();
		d = v.distance();
		v1 += v2;
		EXPECT(v1.x, 0.0f);
		EXPECT(v1.y, 0.0f);
		v1 *= v2;
		EXPECT(v1.x, 0.0f);
		EXPECT(v1.y, 0.0f);
	}

	void testVec3()
	{
		engine::Vector3 v2;
		EXPECT(v2.x, 0.0f);
		EXPECT(v2.y, 0.0f);
		EXPECT(v2.z, 0.0f);
		engine::Vector3 v(1.0f, 0.5f, 0.0f);
		EXPECT(v.x, 1.0f);
		EXPECT(v.y, 0.5f);
		EXPECT(v.z, 0.0f);
		engine::Vector3 v1(v);
		EXPECT(v1.x, 1.0f);
		EXPECT(v1.y, 0.5f);
		v1 = v2;
		EXPECT(v1.x, 0.0f);
		EXPECT(v1.y, 0.0f);
		EXPECT(v1.z, 0.0f);
		auto d = v.distance();
		v.normalize();
		d = v.distance();
		v1 += v2;
		EXPECT(v1.x, 0.0f);
		EXPECT(v1.y, 0.0f);
		EXPECT(v1.y, 0.0f);
		EXPECT(v1.z, 0.0f);
		v1 *= v2;
		EXPECT(v1.x, 0.0f);
		EXPECT(v1.y, 0.0f);
		EXPECT(v1.z, 0.0f);
	}

	void testVectorUtil()
	{
		engine::Vector3 v1(2,2,2);
		engine::Vector3 v2(1,2,4);
		engine::Vector3 vc = engine::VectorUtil::cross(v1, v2);
		EXPECT(vc.x, 4);
		EXPECT(vc.y, -6);
		EXPECT(vc.z, 2);
		auto d = engine::VectorUtil::dot(v1, v2);
		EXPECT(d, 14);
	}
};

#endif