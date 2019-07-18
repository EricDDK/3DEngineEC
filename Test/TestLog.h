#ifndef _TEST_LOG_H__
#define _TEST_LOG_H__

#include "Common/Log.h"

class TestLog
{
public:
	void testLog() 
	{
		engine::log("test log 1 %s", "success");
		engine::log("test log 2 %d", 1);
		engine::log("test log 3 %s %s", "111", "222");
	}
};

#endif