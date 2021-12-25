
#include<cstdarg>
#include<stddef.h>

#include "Utils/Utils.h"

#include<string>
#include<cassert>

namespace XFmt {

	std::string Fmt(const char* _Fmt,...) {
		char* Out = NULL;

		va_list args;
		va_start(args, _Fmt);


		int Size = std::vsnprintf(NULL, 0, _Fmt, args) + 1;
		if (Size <= 0) {
#ifdef _DEBUG
			assert(Size >= 0);
#endif
			return NULL;
		}

		Out = XFmt::Utils::alloc_c_str(Size);

		std::vsnprintf(Out, Size, _Fmt, args);

		va_end(args);

		return std::string(Out, Out + Size - 1);
	}

	char* Fmt_c_buff(const char* _Fmt, ...) {
		char* Out = NULL;
		va_list args;

		va_start(args, _Fmt);
		int Size = std::vsnprintf(NULL, 0, _Fmt, args) + 1;
		if (Size <= 0) {
#ifdef _DEBUG
			assert(Size >= 0);
#endif
			return NULL;
		}

		Out = XFmt::Utils::alloc_c_str(Size);

		std::vsnprintf(Out, Size, _Fmt, args);

		va_end(args);

		return Out;
	}

}
