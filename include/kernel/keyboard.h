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

#define CTRL_SET  (1 << MODKEY_CTRL)
#define ALT_SET   (1 << MODKEY_ALT)
#define SHIFT_SET (1 << MODKEY_SHIFT)

#define SCROLL_LOCK_ON (1 << SCROLL_LOCK_BIT)
#define NUM_LOCK_ON    (1 << NUM_LOCK_BIT)
#define CAPS_LOCK_ON   (1 << CAPS_LOCK_BIT) 

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
