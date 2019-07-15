#ifndef _COMMON_MACRO_H__
#define _COMMON_MACRO_H__

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

#endif // !_COMMON_MACRO_H__
