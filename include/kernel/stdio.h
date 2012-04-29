#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>

int sprintf(char *buf, const char *fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list args);
void printk(const char *fmt, ...);

#endif /* _STDIO_H */
