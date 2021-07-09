#ifdef ARCH_X64
#include <arch\x86_64\mmngr\vmmngr.h>
#endif

void valloc (uint64_t pos) {
	x64_cli();
	map_page ((uint64_t)pmmngr_alloc(), pos);
}

