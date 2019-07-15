#ifndef _TEST_MEMORYPOOL_H__
#define _TEST_MEMORYPOOL_H__

#include "TestCommon.h"
#include "Base/MemoryPool/MemoryTool.h"
#include "Common/3DEngine.h"

ENGINE_NAMESPACE_USE

class Test
{
public:
	Test(int a, double b)
	{
		v = a;
		d = b;
	}
	int v;
	double d;
};

class TestLarge
{
public:
	TestLarge(int a)
	{
		l1 = a;
	}
	long long l1;  long long l2;  long long l3;  long long l4;
	long long l5;  long long l6;  long long l7;  long long l8;
	long long l9;  long long l10; long long l11; long long l12;
	long long l13; long long l14; long long l15; long long l16;
	long long l17; long long l18; long long l19; long long l20;
	long long l21; long long l22; long long l23; long long l24;
	long long l25; long long l26; long long l27; long long l28;
	long long l29; long long l30; long long l31; long long l32;
	long long l33; long long l34; long long l35; long long l36;
	long long l37; long long l38; long long l39; long long l40;
	long long l41; long long l42; long long l43; long long l44;
};

class TestMemoryPool
{
public:
	void testMemoryPool()
	{
		test1();
		test2();
		testLarge();
		testMacro();
		testGC();
#if TARGET_PLATFORM == PLATFORM_WIN32
		testEffect();
		testMallocPerformance();
#endif
		delete MemoryTool::getInstance();
	}

private:
	void test1()
	{
		auto p = MemoryTool::getInstance()->safeMalloc<int>();
		*p = 5;
		MemoryTool::getInstance()->safeFree(p);
		EXPECT(p, NULL);
	}

	void test2()
	{
		auto p = MemoryTool::getInstance()->safeMalloc<Test>(1, 2.0);
		EXPECT(p->v, 1);
		EXPECT(p->d, 2.0);
		MemoryTool::getInstance()->safeFree(p);
	}

	void testLarge()
	{
		auto p = MemoryTool::getInstance()->safeMalloc<TestLarge>(5);
		EXPECT(p->l1, 5);
		MemoryTool::getInstance()->safeFree(p);
	}

	void testMacro()
	{
		// no params construct
		auto p1 = NEW(int);
		*p1 = 1;
		EXPECT(*p1, 1);
		DELET(p1);
		// multiple params construct
		auto p2 = NEW(Test, 1, 2.0);
		EXPECT(p2->v, 1);
		EXPECT(p2->d, 2.0);
		DELET(p2);
		auto p3 = NEW(TestLarge, 5);
		EXPECT(p3->l1, 5);
		DELET(p3);
	}

	void testGC()
	{
		size_t i;
		for (i = 0; i < 128; ++i)
		{
			int *p = new int;
			*p = 65535;
			DELET(p);
		}
		EXPECT(MemoryTool::getInstance()->getPoolColSize(0), i + NODE_MAX_SIZE);
		MemoryTool::getInstance()->gc();
		EXPECT(MemoryTool::getInstance()->getPoolColSize(0), NODE_MAX_SIZE);
	}

#ifdef TARGET_PLATFORM == PLATFORM_WIN32
#include <time.h>
	void testEffect()
	{
		size_t i;
		clock_t start, end;
		start = clock();
		for (i = 0; i < 10000; ++i)
		{
			{
				auto p = MemoryTool::getInstance()->safeMalloc<int>();
				*p = 5;
				MemoryTool::getInstance()->safeFree(p);
			}
			{
				auto q = MemoryTool::getInstance()->safeMalloc<TestLarge>(5);
				MemoryTool::getInstance()->safeFree(q);
			}
		}
		end = clock();
		auto diff1 = end - start;
		std::cout << start << " - " << end << std::endl;
		start = clock();
		for (i = 0; i < 10000; ++i)
		{
			{
				int *p = new int;
				*p = 5;
				delete p;
			}
			{
				TestLarge *q = new TestLarge(5);
				delete q;
			}
		}
		end = clock();
		std::cout << start << " - " << end << std::endl;
		auto diff2 = end - start;
		/*if (diff1 >= diff2)
		{
		EXPECT(1, 2);
		}*/
	}

	void testMallocPerformance()
	{
		clock_t start, end;
		start = clock();
		size_t i;
		for (i = 0; i < 10000; ++i)
		{
			{
				auto p = MemoryTool::getInstance()->safeMalloc<int>();
				*p = 5;
			}
			{
				auto q = MemoryTool::getInstance()->safeMalloc<TestLarge>(5);
			}
		}
		end = clock();
		auto diff1 = end - start;
		std::cout << start << " - " << end << std::endl;
		start = clock();
		for (i = 0; i < 10000; ++i)
		{
			{
				int *p = new int;
				*p = 5;
			}
			{
				TestLarge *q = new TestLarge(5);
				q->l11 = 15;
			}
		}
		end = clock();
		std::cout << start << " - " << end << std::endl;
		auto diff2 = end - start;
		/*if (diff1 >= diff2)
		{
		EXPECT(1, 2);
		}*/
	}
#endif
};

#endif