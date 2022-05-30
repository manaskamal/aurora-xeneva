///!  Copyright (C) Manas Kamal Choudhury 2021
///!
///!  fastcpy -- Faster buffer copying for performance improvements
///!
///!  /PROJECT - Aurora's Xeneva v1.0
///!  /AUTHOR  - Manas Kamal Choudhury
///!
///!===================================================================

#ifndef __FAST_CPY_H__
#define __FAST_CPY_H__

#include <stdint.h>
#include <sys\_xeneva.h>

extern "C" XE_EXPORT void * fastcpy (void* targ, void* src, size_t len);

#endif