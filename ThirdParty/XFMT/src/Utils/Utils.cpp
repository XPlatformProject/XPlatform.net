#include "Utils.h"

#include <memory>
#ifdef _DEBUG
#include <cassert>
#endif

char* XFmt::Utils::alloc_c_str(const uint32_t _Bytes){
	char* ptr = reinterpret_cast<char*>(std::malloc(_Bytes));

#ifdef _DEBUG
	assert(ptr != NULL);
#endif

	std::memset(ptr, 0, _Bytes);

	return ptr;
}
