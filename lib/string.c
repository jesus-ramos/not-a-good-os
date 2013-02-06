/**
 * @file
 *
 * Similar functions to those defined in glibc string header. Functions for
 * handling strings as well as moving data around. This file includes optimized
 * x86 and non-optimized generic versions for each function.
 */

#include <kernel/string.h>

/* Uncomment to use non-optimized versions */
/* #define USE_GENERIC */

#ifdef USE_GENERIC

#include <kernel/types.h>

void *memcpy(void *dest, const void *src, size_t count)
{
    uint8_t *d;
    const uint8_t *s;

    d = (uint8_t *)dest;
    s = (uint8_t *)src;

    while (count--)
        *d++ = *s++;

    return dest;
}

void *memset(void *s, char c, size_t count)
{
    uint8_t *sp;

    sp = (uint8_t *)s;

    while (count--)
        *sp++ = c;

    return s;
}

size_t strlen(const char *s)
{
    const char *sc;

    for (sc = s; *sc; sc++);

    return sc - s;
}

static int __strcmp(const char *s1, const char *s2, size_t n)
{
    size_t i;
    int diff;

    if (n == 0)
        return 0;

    diff = 0;
    i = 0;
    while (*s1 && *s2)
    {
        diff = *s1++ - *s2++;
        if (diff)
            return diff;
        if (++i == n)
            return 0;
    }

    return *s1 ? 1 : *s2 ? -1 : 0;
}

int strcmp(const char *s1, const char *s2)
{
    return __strcmp(s1, s2, -1);
}

int strncmp(const char *s1, const char *s2, size_t n)
{
    return __strcmp(s1, s2, n);
}

#else /* USE_GENERIC */

inline void *memset(void *s, char c, size_t count)
{
    int d0;
    int d1;

    asm volatile ("rep\n\t"
                  "stosb"
                  : "=&c" (d0), "=&D" (d1)
                  : "a" (c), "1" (s), "0" (count)
                  : "memory");
    return s;
}

void *memcpy(void *dest, const void *src, size_t count)
{
    int d0;
    int d1;
    int d2;

    asm volatile ("rep ; movsl\n\t"
                  "movl %4, %%ecx\n\t"
                  "andl $3, %%ecx\n\t"
                  "jz 1f\n\t"
                  "rep ; movsb\n\t"
                  "1:"
                  : "=&c" (d0), "=&D" (d1), "=&S" (d2)
                  : "0" (count / 4), "g" (count),
                    "1" ((long)dest), "2" ((long)src)
                  : "memory");
    return dest;
}

size_t strlen(const char *s)
{
    int d0;
    int res;

    asm volatile ("repne\n\t"
                  "scasb\n\t"
                  "notl %0\n\t"
                  "decl %0"
                  : "=c" (res), "=&D" (d0)
                  : "1" (s), "a" (0), "0" (0xffffffffu)
                  : "memory");
    return res;
}

int strcmp(const char *s1, const char *s2)
{
    int d0;
    int d1;
    int res;

    asm volatile("1:\tlodsb\n\t"
                 "scasb\n\t"
                 "jne 2f\n\t"
                 "testb %%al,%%al\n\t"
                 "jne 1b\n\t"
                 "xorl %%eax,%%eax\n\t"
                 "jmp 3f\n"
                 "2:\tsbbl %%eax,%%eax\n\t"
                 "orb $1,%%al\n"
                 "3:"
                 : "=a" (res), "=&S" (d0), "=&D" (d1)
                 : "1" (s1), "2" (s2)
                 : "memory");
    return res;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
    int res;
    int d0;
    int d1;
    int d2;

    asm volatile("1:\tdecl %3\n\t"
                 "js 2f\n\t"
                 "lodsb\n\t"
                 "scasb\n\t"
                 "jne 3f\n\t"
                 "testb %%al,%%al\n\t"
                 "jne 1b\n"
                 "2:\txorl %%eax,%%eax\n\t"
                 "jmp 4f\n"
                 "3:\tsbbl %%eax,%%eax\n\t"
                 "orb $1,%%al\n"
                 "4:"
                 : "=a" (res), "=&S" (d0), "=&D" (d1), "=&c" (d2)
                 : "1" (s1), "2" (s2), "3" (n)
                 : "memory");
    return res;
}

#endif /* USE_GENERIC */
