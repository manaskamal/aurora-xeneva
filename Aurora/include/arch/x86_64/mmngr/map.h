/**
 *  Copyright (C) Manas Kamal Choudhury 2021
 *
 *  map.h -- Memory Mapping functions for device, file and free memory
 *           mapping
 *
 *  /PROJECT - Aurora Xeneva 
 *  /AUTHOR  - Manas Kamal Choudhury
 *
 * =======================================================================
 */

#ifndef __MAP_H__
#define __MAP_H__

#include <stdint.h>

//! local and global mapping are same as MAP_PRIVATE | MAP_SHARED
//! in unix systems
#define MAP_LOCAL    1    //Local gives access to only mapping process
#define MAP_GLOBAL   2    //global gives access to every processes in the proc list

//! Security Attributes
#define ATTRIBUTE_READ  1
#define ATTRIBUTE_WRITE 2
#define ATTRIBUTE_USER  4

#endif