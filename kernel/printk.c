/**
 * @file
 *
 * Kernel printing functions, currently only supports printing to the screen
 */

#include <kernel/screen.h>
#include <kernel/stdio.h>

char kern_buf[1024];

/**
 * @brief Basic kernel printing function for outputting to the kernel console
 * (currently just the screen)
 *
 * @param[in] fmt string to print to the screen, for now we assume it's as big
 * as 1024 characters. Supports same formatting as glibc printf function.
 */
void printk(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vsprintf(kern_buf, fmt, args);
    fb_put_str(kern_buf);
    va_end(args);
}
