#ifdef ARCH_X64
#include <arch\x86_64\mmngr\paging.h>
#include <arch\x86_64\thread.h>
#endif

#include <string.h>
#include <stdio.h>


void valloc (uint64_t pos) {
	x64_cli();
	void *p = AuPmmngrAlloc();
	AuMapPage((uint64_t)p, pos, PAGING_USER);
}

void vfree (uint64_t pos) {
	x64_cli();
	AuUnmapPage((uint64_t)pos);
}

