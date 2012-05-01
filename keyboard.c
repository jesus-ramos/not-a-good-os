#include <kernel/keyboard.h>
#include <kernel/stdio.h>

#include <asm/interrupt.h>

#define KEY_RELEASED (1 << 8)

static char scancode_table[128] =
{
    0, 0 /* ESC */,
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
    '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i' ,'o', 'p', '[', ']',
    '\n', 0 /* LEFT CTRL */,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0 /* LEFT SHIFT */, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/'
};

void keyboard_callback(struct registers *regs)
{
    uint8_t scancode;
    char v;

    scancode = inportb(0x60);
    if (!(scancode & KEY_RELEASED))
    {
        v = scancode_table[scancode];
        if (v)
            printk("%c", v);
    }
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}
