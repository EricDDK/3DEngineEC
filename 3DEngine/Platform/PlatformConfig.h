#ifndef _PLATFORM_PLATFORMCONFIG_H__
#define _PLATFORM_PLATFORMCONFIG_H__

#include "../Common/Macro.h"

// deprecated
enum class Platform : int
{
	None = 0,
	Win32 = 1,
	iOS = 2,
	Android = 3,
	Mac = 4,
};

#define PLATFORM_NONE 0
#define PLATFORM_WIN32 1
#define PLATFORM_IOS 2
#define PLATFORM_ANDROID 3
#define PLATFORM_MAC 4

#define TARGET_PLATFORM PLATFORM_NONE

// iOS
#if defined(__APPLE__) && !defined(ANDROID)
#include <TargetConditionals.h>
	#if TARGET_OS_IPHONE
		#undef  TARGET_PLATFORM
		#define TARGET_PLATFORM PLATFORM_IOS
	#elif TARGET_OS_MAC
		#undef  TARGET_PLATFORM
		#define TARGET_PLATFORM PLATFORM_MAC
	#endif
#endif

// android
#if defined(ANDROID)
#undef  TARGET_PLATFORM
#define TARGET_PLATFORM PLATFORM_ANDROID
#endif

// windows
#if defined(_WIN32) || defined(_WINDOWS)
	#undef  TARGET_PLATFORM
	#define TARGET_PLATFORM PLATFORM_WIN32
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

#endif // !_PLATFORM_PLATFORMCONFIG_H__
