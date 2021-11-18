#ifndef __UTILS_7C93E23E270F0C7E1773E9CC6E60E394_H__
#define __UTILS_7C93E23E270F0C7E1773E9CC6E60E394_H__

#include <stddef.h>

void tcal_bzero(void *p, size_t len);

void tcal_bcopy4rev(void *dest, const void *src, size_t len);

void tcal_brev(void *p, size_t len);

void tcal_bcopy(void *dest, const void *src, size_t len);

void tcal_bcopy4insert(void *dest, const void *src, size_t len);

void tcal_bcopy4remove(void *dest, const void *src, size_t len);


#endif //__UTILS_7C93E23E270F0C7E1773E9CC6E60E394_H__
