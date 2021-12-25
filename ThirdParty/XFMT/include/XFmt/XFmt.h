#ifndef _INC_XFMT_H
#define _INC_XFMT_H

#include<stddef.h>
#include<string>

namespace XFmt {
	std::string Fmt(const char* Fmt,...);

	char* Fmt_c_buff(const char* Fmt,...);
}

#endif