#ifndef _SCREEN_H
#define _SCREEN_H

#include <kernel/types.h>

void vga_init();
void vga_put_char(char c);
void vga_put_str(char *str);

#endif /* _SCREEN_H */
