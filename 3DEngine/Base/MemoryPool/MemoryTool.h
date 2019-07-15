#ifndef _MEMORY_TOOL_H__
#define _MEMORY_TOOL_H__

#include "MemoryPool.h"

#ifndef NEW
#define NEW(T, ...) MemoryTool::getInstance()->safeMalloc<T>(##__VA_ARGS__);
#endif // !NEW

#ifndef DELET
#define DELET(p) MemoryTool::getInstance()->safeFree(p);
#endif // !DELET

static engine::MemoryPool *s_pool = new engine::MemoryPool;

class MemoryTool
{
public:
	static engine::MemoryPool *getInstance()
	{
		return s_pool;
	}
};

#endif
