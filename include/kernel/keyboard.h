#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#define MODKEY_CTRL  (1 << 0)
#define MODKEY_ALT   (1 << 1)
#define MODKEY_SHIFT (1 << 2)

#define SCROLL_LOCK (1 << 0)
#define CAPS_LOCK   (1 << 1)
#define NUM_LOCK    (1 << 2)

#include <kernel/types.h>

struct keypress_data
{
    uint8_t scancode;
    char key;
    char released : 1;
    int modifier_keys : 3;
    int lock_keys : 3;
};

extern char scancode_table[];

void init_keyboard();

#endif /* _KEYBOARD_H */
