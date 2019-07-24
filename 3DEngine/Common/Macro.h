#ifndef _COMMON_MACRO_H__
#define _COMMON_MACRO_H__

#include <assert.h>

#ifdef __cplusplus
	#ifndef ENGINE_NAMESPACE_START
	#define ENGINE_NAMESPACE_START namespace engine {
	#endif // !ENGINE_NAMESPACE_START {

	#ifndef ENGINE_NAMESPACE_END
	#define ENGINE_NAMESPACE_END }
	#endif // !ENGINE_NAMESPACE_END

	#ifndef ENGINE_NAMESPACE_USE
	#define ENGINE_NAMESPACE_USE using namespace engine;
	#endif // !ENGINE_NAMESPACE_USE
#else
	#define ENGINE_NAMESPACE_START
	#define ENGINE_NAMESPACE_END
	#define ENGINE_NAMESPACE_USE
#endif 

#ifdef _WIN32
	#ifndef EC_DLL
	#define EC_DLL __declspec(dllexport)
	#endif // !ET_DLL
#else
	#ifndef ET_DLL
	#define ET_DLL __attribute__((visibility("default")))
	#endif // !ET_DLL
#endif

#ifndef EC_ASSERT
#define EC_ASSERT assert
#endif // !ET_ASSERT


#endif // !_COMMON_MACRO_H__
