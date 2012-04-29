#include <kernel/screen.h>
#include <kernel/stdio.h>

char kern_buf[1024];

void printk(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vsprintf(kern_buf, fmt, args);
    fb_put_str(kern_buf);
    va_end(args);
}
