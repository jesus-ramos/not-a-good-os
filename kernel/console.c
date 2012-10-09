#include <kernel/console.h>
#include <kernel/keyboard.h>
#include <kernel/stdio.h>

void handle_console_input(const struct keyevent_data *keyevent)
{
    if (keyevent->key && !keyevent->released)
        printk("%c", keyevent->key);
}

void init_console()
{
    register_keyboard_handler(handle_console_input);
}
