#include "screen.h"

volatile char *fb = (volatile char *)0xb8000;

void prints(const char *str, int color)
{
    while (*str)
    {
        *fb++ = *str++;
        *fb++ = color;
    }
}
