#ifdef ARCH_X64
#include <arch\x86_64\mmngr\vmmngr.h>
#include <arch\x86_64\thread.h>
#endif

#include <string.h>
#include <stdio.h>


void valloc (uint64_t pos) {
	void *p = pmmngr_alloc();
	memset(p, 0, 4096);
	map_page ((uint64_t)p, pos, PAGING_USER);
}

void vfree (uint64_t pos) {
	x64_cli();
	unmap_page ((uint64_t)pos);
}
