#ifndef STRING_H
#define STRING_H

#include <stddef.h>

size_t strlen(const char* String);
int memcmp(const void *S1, const void *S2, size_t Size);
void *memcpy(void *Dest, const void *Src, size_t Size);
void *memmove(void *Dest, const void *Src, size_t Size);
void *memset(void *s, int c, size_t n);

#endif
