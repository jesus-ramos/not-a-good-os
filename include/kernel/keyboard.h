#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <kernel/types.h>

/**
 * @brief Enumeration for keeping track of the state of the modifier keys on the
 * keyboard
 */
enum mod_key_bits
{
    MODKEY_CTRL,
    MODKEY_ALT,
    MODKEY_SHIFT
};

/**
 * @brief Enumeration for keeping track of which of the LOCK keys are enabled
 * and for setting the LED lights for them
 */
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

#define ESCAPE      0x01
#define CTRL        0x1D
#define LEFT_SHIFT  0x2A
#define RIGHT_SHIFT 0x36
#define ALT         0x38
#define CAPS_LOCK   0x3A
#define F1          0x3B
#define F2          0x3C
#define F3          0x3D
#define F4          0x3E
#define F5          0x3F
#define F6          0x40
#define F7          0x41
#define F8          0x42
#define F9          0x43
#define F10         0x44
#define NUM_LOCK    0x45
#define SCROLL_LOCK 0x46
#define F11         0x57
#define F12         0x58

/**
 * @brief Represents the state of the keyboard. Knows what modifier and LOCK
 * keys are currently set.
 */
struct keyboard_state
{
    uint8_t modifier_keys;
    uint8_t lock_keys;
};

/**
 * @brief Data for a key event (down/up) along with the associated keyboard
 * state at the time of the keypress
 */
struct keyevent_data
{
    uint8_t scancode;
    char key;
    uint8_t released;
    struct keyboard_state kb_state;
};

typedef void (*keyboard_handler_t)(const struct keyevent_data *);

void init_keyboard();
void register_keyboard_handler(keyboard_handler_t handler);

extern struct keyboard_state kb_state;

/**
 * @brief Checks if the scancode for a key is from a key on the keypad
 *
 * @param scancode the scancode to check
 *
 * @return 1 if the scancode is from a key on the keypad, 0 otherwise
 */
static inline int is_keypad_key(uint8_t scancode)
{
    return (scancode >= 0x47 && scancode <= 0x53) || scancode == 0x37;
}

/**
 * @brief Checks if the scancode for a key is from the top numeric row of the
 * keyboard
 *
 * @param scancode the scancode to check
 *
 * @return 1 if the scancode is from a key on the top numeric row of the
 * keyboard, 0 otherwise
 */
static inline int is_numeric_row_key(uint8_t scancode)
{
    return (scancode >= 0x02 && scancode <= 0x0D) || scancode == 0x29;
}

/**
 * @brief Checks if a scancode is for a modifier key
 *
 * @param scancode the scancode to check
 *
 * @return 1 if the scancode is for a modifier key, 0 otherwise
 */
static inline int is_modifier_key(uint8_t scancode)
{
    return scancode == LEFT_SHIFT || scancode == RIGHT_SHIFT || scancode == ALT
        || scancode == CTRL;
}

/**
 * @brief Checks if a scancode is for a function (FN) key
 *
 * @param scancode the scancode to check
 *
 * @return 1 if the scancode is for a function key, 0 otherwise
 */
static inline int is_function_key(uint8_t scancode)
{
    return (scancode >= 0x3B && scancode <= 0x44) ||
        scancode == 0x57 || scancode == 0x58;
}

#endif /* _KEYBOARD_H */
