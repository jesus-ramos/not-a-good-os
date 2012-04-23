#include <kernel/string.h>

void *memcpy(void *dest, const void *src, size_t n)
{
    uint8_t *d;
    const uint8_t *s;

    d = (uint8_t *)dest;
    s = (uint8_t *)src;
    
    while (n--)
        *d++ = *s++;

    return dest;
}

void *memset(void *s, int c, size_t n)
{
    uint8_t *sp;

    sp = (uint8_t *)s;
    
    while (n--)
        *sp++ = c;
    
    return s;
}

size_t strlen(const char *s)
{
    size_t len = 0;

    while (*s++)
        len++;

    return len;
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
        i++;
        if (i == n)
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
