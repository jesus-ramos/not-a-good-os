#include <kernel/screen.h>
#include <kernel/types.h>

#include <asm/port_comm.h>

#define VGA_TELL      0x3D4
#define VGA_SEND      0x3D5
#define VGA_HIGH_BYTE 14
#define VGA_LOW_BYTE  15

#define ATTR_BYTE(fore_color, back_color) ((back_color << 4) | (fore_color & 0x0F))
#define ATTR(fore_color, back_color) (ATTR_BYTE(fore_color, back_color) << 8)
#define BLANK (0x20 | (ATTR_BYTE(WHITE, BLACK) << 8))

#define BLACK 0
#define WHITE 15

uint16_t cursor_x = 0;
uint16_t cursor_y = 0;

volatile uint16_t *fb_mem = (volatile uint16_t *)0xb8000;

static void fb_move_cursor()
{
    uint16_t cursor_loc;

    cursor_loc = cursor_y * 80 + cursor_x;
    outportb(VGA_TELL, VGA_HIGH_BYTE);
    outportb(VGA_SEND, cursor_loc >> 8);
    outportb(VGA_TELL, VGA_LOW_BYTE);
    outportb(VGA_SEND, cursor_loc);
}

static void fb_scroll()
{
    int i;

    if (cursor_y >= 25)
    {
        for (i = 0; i < 24 * 80; i++)
            fb_mem[i] = fb_mem[i + 80];
        for (i = 24 * 80; i < 25 * 80; i++)
            fb_mem[i] = BLANK;
        cursor_y = 24;
    }
}

void fb_put_char(char c)
{
    volatile uint16_t *loc;

    switch (c)
    {
        case '\b':
            if (cursor_x) cursor_x--;
            break;
        case '\t':
            cursor_x = (cursor_x + 8) & ~7;
            break;
        case '\r':
            cursor_x = 0;
            break;
        case '\n':
            cursor_x = 0;
            cursor_y++;
            break;
        default:
            loc = fb_mem + cursor_y * 80 + cursor_x;
            *loc = c | ATTR(WHITE, BLACK);
            cursor_x++;
    }

    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y++;
    }

    fb_scroll();
    fb_move_cursor();
}

void fb_clear()
{
    int i;

    for (i = 0; i < 25 * 80; i++)
        fb_mem[i] = BLANK;

    cursor_x = 0;
    cursor_y = 0;
    fb_move_cursor();
}

void fb_put_str(char *str)
{
    while (*str)
        fb_put_char(*str++);
}
