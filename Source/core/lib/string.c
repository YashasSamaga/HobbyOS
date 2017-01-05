/********************************************************************************/
//Lindus Kernel String Lib
//Author  :   Yashas Samaga
//Date    :   21-04-2012
//Description: String Functions
//
//Copyright (C) Yashas Samaga <yashas_2010@yahoo.com>
/********************************************************************************/
#include <lib\string.h>
//////////////////////////////////////////////////////////////////////////////////
void *memcpy(void *dest, const void *src, int count)
{
	const char *sp = (const char *)src;
	char *dp = (char *)dest;
	for(; count != 0; count--) *dp++ = *sp++;
	return dest;
}
void *memset(void *dest, char val,int count)
{
	char *temp = (char *)dest;
	for( ; count != 0; count--) *temp++ = val;
	return dest;
}
unsigned short *memsetw(unsigned short *dest, unsigned short val,int count)
{
	unsigned short *temp = (unsigned short *)dest;
	for( ; count != 0; count--) *temp++ = val;
	return dest;
}
int memcmp(const void *p1, const void *p2, int n) 
{
	
	unsigned char *v1 = (void*) p1;
	unsigned char *v2 = (void*) p2;
	int i;
	for (i = 0; i < n; i++) 
	{
		if (v1[i] != v2[i]) 
		{
			return 1;
		}
	}

	return 0;
}
void *memmove(void *d, const void *s, int n) 
{
	int i;
	unsigned char *dst = (unsigned char*) d;
	unsigned char *src = (unsigned char*) s;

	if (src == dst) {
		return dst;
	}
	else if (src > dst) {
		for (i = 0; i < n; i++) {
			dst[i] = src[i];
		}
	}
	else if (src < dst) {
		for (i = 0; i < n; i++) {
			dst[n - i - 1] = src[n - i - 1];
		}
	}
	return dst;
} 
int strlen(const char *str)
{
	int retval;
	for(retval = 0; *str != '\0'; str++) retval++;
	return retval;
}
int strcmp(const char *s1, const char *s2)
{
	int i;

	for (i = 0;; i++) 
	{
		if (s1[i] == s2[i]) 
		{
			if (s1[i] == '\0') return 0;
			continue;
		}
		if (s1[i] == '\0') return -1;
		if (s2[i] == '\0') return 1;
		if (s1[i] < s2[i]) return -1;
		else return 1;
	}
}
char *strcpy(char *d, const char *s) 
{
	int i;

	for (i = 0; s[i] != '\0'; i++) 
	{
		d[i] = s[i];
	}
	d[i] = '\0';
	return d;
}
char *strcat(char *d, const char *s) 
{
	int i, e;

	for (e = 0; d[e] != '\0'; e++);

	for (i = 0; s[i] != '\0'; i++) 
	{
		d[e + i] = s[i];
	}
	d[e + i] = '\0';
	return d;
}

