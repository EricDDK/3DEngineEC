
#include "Log.h"

ENGINE_NAMESPACE_START

void log(const char * format, ...)
{
	int bufferSize = MAX_LOG_LENGTH;
	char* buf = nullptr;
	int nret = 0;
	va_list args;
	do
	{
		buf = new (std::nothrow) char[bufferSize];
		if (buf == nullptr)
			return;
		va_start(args, format);
		nret = vsnprintf(buf, bufferSize - 3, format, args);
		va_end(args);
		if (nret >= 0)
		{
			if (nret <= bufferSize - 3)
			{
				break;
			}
			else
			{
				bufferSize = nret + 3;
				delete[] buf;
			}
		}
		else
		{
			bufferSize *= 2;
			delete[] buf;
		}
	} while (true);
	buf[nret] = '\0';
	std::cout << buf << std::endl;
}

ENGINE_NAMESPACE_END