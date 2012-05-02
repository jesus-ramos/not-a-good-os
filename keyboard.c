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

struct keyboard_state
{
    int modifier_keys : 3;
    int lock_keys : 3;
} kb_state;

/* Standard EN-US Keyboard */
char scancode_table[] =
{
    [0x02] = '1',
    [0x03] = '2',
    [0x04] = '3',
    [0x05] = '4',
    [0x06] = '5',
    [0x07] = '6',
    [0x08] = '7',
    [0x09] = '8',
    [0x0A] = '9',
    [0x0B] = '0',
    [0x0C] = '-',
    [0x0D] = '=',
    [0x0E] = '\b',
    [0x0F] = '\t',
    
    [0x10] = 'q',
    [0x11] = 'w',
    [0x12] = 'e',
    [0x13] = 'r',
    [0x14] = 't',
    [0x15] = 'y',
    [0x16] = 'u',
    [0x17] = 'i',
    [0x18] = 'o',
    [0x19] = 'p',
    [0x1A] = '[',
    [0x1B] = ']',
    [0x1C] = '\n',

    [0x1E] = 'a',
    [0x1F] = 's',
    [0x20] = 'd',
    [0x21] = 'f',
    [0x22] = 'g',
    [0x23] = 'h',
    [0x24] = 'j',
    [0x25] = 'k',
    [0x26] = 'l',
    [0x27] = ';',
    [0x28] = '\'',
    [0x29] = '`',

    [0x2B] = '\\',
    [0x2C] = 'z',
    [0x2D] = 'x',
    [0x2E] = 'c',
    [0x2F] = 'v',
    [0x30] = 'b',
    [0x31] = 'n',
    [0x32] = 'm',
    [0x33] = ',',
    [0x34] = '.',
    [0x35] = '/',

    [0x37] = '*', /* KEYPAD */
    [0x39] = ' ',

    /* KEYPAD */
    [0x47] = '7',
    [0x48] = '8',
    [0x49] = '9',
    [0x4A] = '-',
    [0x4B] = '4',
    [0x4C] = '5',
    [0x4D] = '6',
    [0x4E] = '+',
    [0x4F] = '1',
    [0x50] = '2',
    [0x51] = '3',
    [0x52] = '0',
    [0x53] = '.'
};

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

void handle_keyboard(struct registers *regs)
{
    uint8_t scancode;
    char v;

    send_eoi();
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
