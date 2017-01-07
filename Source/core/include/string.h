/******************************************************************************/
//	Generic String Library
//
//	Standard String Library Routines Implementation
//
//	string.h
//	Date: January 5th 2017
//
/******************************************************************************/
#ifndef __STRING_H
#define __STRING_H

#include <size_t.h>
#include <stdint.h>

#define NULL (void*)0

extern char *strcpy(char *s1, const char *s2);
extern size_t strlen (const char* str);
extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern uint16_t *memsetw(uint16_t *dest, uint16_t val, size_t count);
extern int memcmp(const void* aptr, const void* bptr, size_t size);
extern void* memmove(void* dstptr, const void* srcptr, size_t size);


#endif // __STRING_H
