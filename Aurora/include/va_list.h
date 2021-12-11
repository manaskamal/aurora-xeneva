/**
 *   Copyright (C) Manas Kamal Choudhury 2020
 *
 * va_list --- ?
 *
 * /PROJECT - Aurora 
 * /AUTHOR  - Manas Kamal Choudhury
 *
 **/

#ifndef __VA_LIST_H__
#define __VA_LIST_H__

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef _VALIST
#define _VALIST
typedef unsigned char *_va_list_;
typedef unsigned char * va_list;
#endif

#ifdef __cplusplus
}
#endif


#define STACKITEM int

#define VA_SIZE(TYPE)   \
	((sizeof(TYPE) + sizeof(STACKITEM) - 1) \
	& ~(sizeof(STACKITEM) - 1))

#define va_start(AP, LASTARG) \
	(AP=((_va_list_)&(LASTARG) + VA_SIZE(LASTARG)))

#define va_end(AP)

#define va_arg(AP, TYPE)  \
	(AP += VA_SIZE(TYPE) , *((TYPE *)(AP - VA_SIZE(TYPE))))

#endif