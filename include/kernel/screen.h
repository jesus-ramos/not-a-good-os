#ifndef _SCREEN_H
#define _SCREEN_H

#include <kernel/types.h>

void fb_put_char(char c);
void fb_clear();
void fb_put_str(char *str);
void fb_put_uint32(uint32_t num);

#endif /* _SCREEN_H */
