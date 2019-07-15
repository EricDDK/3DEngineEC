#ifndef _PLATFORM_PLATFORMCONFIG_H__
#define _PLATFORM_PLATFORMCONFIG_H__

#include "../Common/Macro.h"

ENGINE_NAMESPACE_START

enum class Platform : int
{
	None = 0,
	Win32 = 1,
	iOS = 2,
	Android = 3,
	Mac = 4,

};

#define TARGET_PLATFORM Platform::None

// iOS
#if defined(__APPLE__) && !defined(ANDROID)
#include <TargetConditionals.h>
	#if TARGET_OS_IPHONE
		#undef  TARGET_PLATFORM
		#define TARGET_PLATFORM Platform::iOS
	#elif TARGET_OS_MAC
		#undef  TARGET_PLATFORM
		#define TARGET_PLATFORM Platform::Mac
	#endif
#endif

// android
#if defined(ANDROID)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM Platform::Android
#endif

// windows
#if defined(_WIN32) || defined(_WINDOWS)
	#undef  TARGET_PLATFORM
	#define TARGET_PLATFORM Platform::Win32
#endif

// 64 bits OS
#if defined(_M_X64) || defined(_WIN64) \
|| defined(__LP64__) || defined(_LP64) \
|| defined(__x86_64) || defined(__arm64__) \
|| defined(__aarch64__)
	#define OS_64BIT true
#else
	#define OS_64BIT false
#endif // judge is 64 bit

ENGINE_NAMESPACE_END

#endif // !_PLATFORM_PLATFORMCONFIG_H__
