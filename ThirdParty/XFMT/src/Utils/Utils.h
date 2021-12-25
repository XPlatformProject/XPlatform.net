#ifndef _XFMT_UTILS_H
#define _XFMT_UTILS_H

#include<stdint.h>
#include<stddef.h>

namespace XFmt {
	namespace Utils {
		char* alloc_c_str(const uint32_t _Bytes);
	}
}

#endif