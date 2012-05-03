#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <kernel/types.h>

#define MODKEY_CTRL  1
#define MODKEY_ALT   2
#define MODKEY_SHIFT 3

#define SCROLL_LOCK_FLAG 1
#define NUM_LOCK_FLAG    2
#define CAPS_LOCK_FLAG   3

struct keypress_data
{
    uint8_t scancode;
    char key;
    uint8_t released;
    uint8_t modifier_keys;
    uint8_t lock_keys;
};

extern char scancode_table[];

void init_keyboard();

#endif /* _KEYBOARD_H */
