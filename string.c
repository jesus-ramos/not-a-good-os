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
