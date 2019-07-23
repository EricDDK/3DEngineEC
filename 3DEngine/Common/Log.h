#ifndef _COMMON_LOG_H__
#define _COMMON_LOG_H__

#include "iostream"
#include <stdarg.h>
#include "../Platform/PlatformConfig.h"

#define MAX_LOG_LENGTH 1024

ENGINE_NAMESPACE_START

void log(const char * format, ...);

ENGINE_NAMESPACE_END

#endif