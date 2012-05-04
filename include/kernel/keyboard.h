#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <kernel/types.h>

enum mod_key_bits
{
    MODKEY_CTRL,
    MODKEY_ALT,
    MODKEY_SHIFT
};

enum lock_key_bits
{
    SCROLL_LOCK_BIT,
    NUM_LOCK_BIT,
    CAPS_LOCK_BIT
};

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
