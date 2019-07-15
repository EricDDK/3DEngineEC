#ifndef _MEMORY_POOL_H__
#define _MEMORY_POOL_H__

#ifndef MP_LOG
#define MP_LOG(msg) do {std::cout << msg << std::endl;} while(0)
#endif // log define

#include "../../Common/Macro.h"
#include <assert.h>
#include <vector>
#include <stack>
#include <mutex>
#include "stdio.h"

#ifndef MEM_ALIGN_FACTOR
#if OS_64BIT
#define MEM_ALIGN_FACTOR 4
#else
#define MEM_ALIGN_FACTOR 4
#endif // OS_64BIT
#endif // !MEM_ALIGN_FACTOR

#ifndef POOL_MAX_BYTES
#define POOL_MAX_BYTES MEM_ALIGN_FACTOR * 32
#endif // !POOL_MAX_BYTES

#ifndef POOL_MAX_SIZE
#define POOL_MAX_SIZE POOL_MAX_BYTES / MEM_ALIGN_FACTOR
#endif // !POOL_MAX_SIZE 32

#ifndef NODE_MAX_SIZE
#define NODE_MAX_SIZE 128
#endif // !NODE_MAX_SIZE

// class
ENGINE_NAMESPACE_START

class MemoryPool
{
public:
	MemoryPool()
		:_pool(std::vector<std::stack<void*>>(POOL_MAX_SIZE))
	{
		size_t i, j;
		for (i = 0; i < POOL_MAX_SIZE; ++i)
		{
			for (j = 0; j < NODE_MAX_SIZE; ++j)
			{
				//MP_LOG((i + 1) * MEM_ALIGN_FACTOR);
				void* p = malloc((i + 1) * MEM_ALIGN_FACTOR);
				_pool[i].push(p);
			}
		}
	}

	~MemoryPool()
	{
		_mtx.lock();
		for (auto& s : _pool)
		{
			while (!s.empty())
			{
				auto v = s.top();
				s.pop();
				delete v;
			}
		}
		_mtx.unlock();
	}

	template<typename T, typename... Args>
	T* safeMalloc(Args&&... args)
	{
        size_t size = sizeof(T);
        size_t index = size / 4 - 1;
		_mtx.lock();
		if (size > POOL_MAX_BYTES || _pool[index].empty())
		{
			_mtx.unlock();
			void *pointer = malloc(size);
			return new(pointer) T(std::forward<Args>(args)...);
		}
		else
		{
			if (_pool[index].empty())
				return new T(std::forward<Args>(args)...);
			void *pointer = _pool[index].top();
			_pool[index].pop();
			_mtx.unlock();
			return new(pointer) T(std::forward<Args>(args)...);
		}
	}

	template<typename T>
	void safeFree(T* &t)
	{
        size_t size = sizeof(T);
        size_t index = size / 4 - 1;
		if (size > POOL_MAX_BYTES)
		{
			t->~T();
			delete t;
		}
		else
		{
			_mtx.lock();
			_pool[index].push(t);
			_mtx.unlock();
			t = NULL;
		}
	}

	void gc()
	{
		_mtx.lock();
		for (auto& s : _pool)
		{
			size_t size = s.size();
			while (size-- > NODE_MAX_SIZE)
			{
				void *p = s.top();
				s.pop();
				delete(p);
			}
		}
		_mtx.unlock();
	}

	// test function
	const size_t getPoolColSize(int index)
	{
		return _pool[index].size();
	}

private:
	std::vector<std::stack<void*>> _pool;
	std::mutex _mtx;
};

ENGINE_NAMESPACE_END

#endif
