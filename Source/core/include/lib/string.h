/********************************************************************************/
//Lindus Kernel String Lib
//Author  :   Yashas Samaga
//Date    :   21-04-2012
//Description: String Functions
//
//Copyright (C) Yashas Samaga <yashas_2010@yahoo.com>
/********************************************************************************/
#ifndef _STRING_H
#define _STRING_H

extern void *memcpy(void *dest, const void *src, int count);
extern void *memset(void *dest, char val,int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val,int count);
extern int strlen(const char *str);
extern int memcmp(const void *p1, const void *p2, int n);
extern void *memmove(void *d, const void *s, int n); 
extern int strcmp(const char *s1, const char *s2);
extern char *strcpy(char *d, const char *s);
extern char *strcat(char *d, const char *s); 

#endif
