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

ENGINE_NAMESPACE_END

#endif // !_PLATFORM_PLATFORMCONFIG_H__
