/**
 * @file
 *
 * Simple console implementation, just handles keyboard events and outputs them
 * to the screen
 */

#include <kernel/console.h>
#include <kernel/ctype.h>
#include <kernel/keyboard.h>
#include <kernel/shutdown.h>
#include <kernel/stdio.h>

/**
 * @brief Called from handle_keyboard() whenever a keyboard event happens to
 * simply output the pressed key onto the screen
 *
 * @param[in] keyevent the information for the keypress that happened
 */
void handle_console_input(const struct keyevent_data *keyevent)
{
    /* CTRL + C to shutdown for now */
    if (tolower(keyevent->key) == 'c' &&
        (keyevent->kb_state.modifier_keys & CTRL_SET))
        shutdown();

    if (keyevent->key && !keyevent->released)
        printk("%c", keyevent->key);
}

/**
 * @brief Console initialization function to register the console handler with
 * the keyboard handler
 */
void init_console()
{
    register_keyboard_handler(handle_console_input);
}
