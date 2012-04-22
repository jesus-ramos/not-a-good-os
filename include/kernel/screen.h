#ifndef _SCREEN_H
#define _SCREEN_H

#include <kernel/types.h>

void fb_put_char(char c);
void fb_clear();
void fb_put_str(char *str);

#endif /* _SCREEN_H */
