#ifndef _STRING_H
#define _STRING_H

#include <kernel/types.h>

void *memcpy(void *dest, const void *src, size_t count);
void *memset(void *s, char c, size_t count);

size_t strlen(const char *s);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);

#endif /* _STRING_H */
