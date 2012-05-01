#include <kernel/keyboard.h>
#include <kernel/stdio.h>

#include <asm/interrupt.h>

#define KEYBOARD_IRQ IRQ1

#define KEY_RELEASED (1 << 7)

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_CMD_PORT  0x64

#define KEYBOARD_BUSY    0x02
#define KEYBOARD_DISABLE 0xAD
#define KEYBOARD_ENABLE  0xAE

static inline void keyboard_wait()
{
    while (inportb(KEYBOARD_DATA_PORT) & KEYBOARD_BUSY);
}

static inline void send_cmd(uint8_t cmd)
{
    keyboard_wait();
    outportb(KEYBOARD_CMD_PORT, cmd);
}

static inline void disable_keyboard()
{
    send_cmd(KEYBOARD_DISABLE);
}

static inline void enable_keyboard()
{
    send_cmd(KEYBOARD_ENABLE);
}

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

void handle_keyboard(struct registers *regs)
{
    uint8_t scancode;
    char v;
    
    scancode = inportb(KEYBOARD_DATA_PORT);
    if (!(scancode & KEY_RELEASED))
    {
        v = scancode_table[scancode];
        if (v)
            printk("%c", v);
    }
}

void init_keyboard()
{
    register_interrupt_handler(KEYBOARD_IRQ, handle_keyboard);
}
