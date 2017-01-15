/******************************************************************************/
//	Generic String Library
//
//	Standard String Library Routines Implementation
//
//	string.c
//	Date: January 5th 2017
//
/******************************************************************************/
#include <string.h>
#include <stdint.h>

char *strcpy(char *s1, const char *s2)
{
    char *s1_p = s1;
    while ((*s1++ = *s2++));
    return s1_p;
}

size_t strlen (const char* str) 
{
	size_t len = 0;
	while (str[len++]);
	return len;
}

void *memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

int memcmp(const void* aptr, const void* bptr, size_t size) 
{
	const unsigned char* a = (const unsigned char*) aptr;
	const unsigned char* b = (const unsigned char*) bptr;
	for (size_t i = 0; i < size; i++) 
	{
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
}

void* memmove(void* dstptr, const void* srcptr, size_t size) 
{
	unsigned char *dst = (unsigned char*) dstptr;
	const unsigned char *src = (const unsigned char*) srcptr;
	if (dst < src) 
	{
		for (size_t i = 0; i < size; i++)
			dst[i] = src[i];
	} 
	else 
	{
		for (size_t i = size; i != 0; i--)
			dst[i-1] = src[i-1];
	}
	return dstptr;
}