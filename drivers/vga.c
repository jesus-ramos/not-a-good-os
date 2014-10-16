/** @file
 *
 * Basic VGA frame buffer driver
 */

#include <kernel/screen.h>
#include <kernel/types.h>

#include <asm/common.h>

#define VGA_CMD       0x3D4
#define VGA_DATA      0x3D5
#define VGA_HIGH_BYTE 14
#define VGA_LOW_BYTE  15

/**
 * @brief All colors supported by VGA display
 */
enum vga_color
{
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GREY,
    DARK_GREY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    LIGHT_BROWN,
    WHITE
};

typedef uint8_t vga_color_t;
typedef uint16_t vga_char_t;

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

size_t cursor_x = 0;
size_t cursor_y = 0;
vga_color_t vga_term_color;
volatile vga_char_t *vid_mem = (volatile uint16_t *)0xb8000;

/**
 * @brief Create a vga character color
 *
 * @param fg_color the foreground color of the character
 * @param bg_color the background color of the character
 *
 * @return a vga_color_t consisting of fg_color and bg_color
 */
static inline vga_color_t make_vga_color(enum vga_color fg_color,
                                         enum vga_color bg_color)
{
    return fg_color | (bg_color << 4);
}

/**
 * @brief Create a vga displayable character
 *
 * @param c the character to display
 * @param color the color the character should be
 */
static inline vga_char_t make_vga_char(char c, vga_color_t color)
{
    return c | color << 8;
}

#define BLANK (make_vga_char(0x20, vga_term_color))

/**
 * @brief Move the frame buffer cursor to the appropriate location on screen
 */
static void vga_move_cursor()
{
    vga_char_t cursor_loc;

    cursor_loc = cursor_y * VGA_WIDTH + cursor_x;

    outportb(VGA_CMD, VGA_HIGH_BYTE);
    outportb(VGA_DATA, cursor_loc >> 8);
    outportb(VGA_CMD, VGA_LOW_BYTE);
    outportb(VGA_DATA, cursor_loc);
}

/**
 * @brief Scroll the frame buffer if necessary
 */
static void vga_scroll()
{
    int i;

    if (cursor_y >= VGA_HEIGHT)
    {
        for (i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++)
            vid_mem[i] = vid_mem[i + VGA_WIDTH];
        for (i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < VGA_HEIGHT * VGA_WIDTH; i++)
            vid_mem[i] = BLANK;
        cursor_y = VGA_HEIGHT - 1;
    }
}

#define VGA_LOCATION (vid_mem + cursor_y * VGA_WIDTH + cursor_x)

/**
 * @brief Put a character onto the screen
 *
 * @param c Character to put on the screen
 */
void vga_put_char(char c)
{
    volatile vga_char_t *loc;

    switch (c)
    {
        case '\b':
            if (cursor_x)
            {
                cursor_x--;
                loc = VGA_LOCATION;
                *loc = BLANK;
            }
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
            loc = VGA_LOCATION;
            *loc = make_vga_char(c, vga_term_color);
            cursor_x++;
    }

    if (cursor_x >= VGA_WIDTH)
    {
        cursor_x = 0;
        cursor_y++;
    }

    vga_scroll();
    vga_move_cursor();
}

#undef VGA_LOCATION

/**
 * @brief Clear the framebuffer
 */
void vga_clear()
{
    int i;

    for (i = 0; i < VGA_HEIGHT * VGA_WIDTH; i++)
        vid_mem[i] = BLANK;

    cursor_x = 0;
    cursor_y = 0;
    vga_move_cursor();
}

/**
 * @brief Put a string on the screen
 *
 * @param[in] str The string to place on the screen, assumes standard null
 * terminated c string
 */
void vga_put_str(char *str)
{
    while (*str)
        vga_put_char(*str++);
}

/**
 * @brief Initialize the VGA display
 */
void vga_init()
{
    vga_term_color = make_vga_color(LIGHT_GREEN, BLACK);
    vga_clear();
}
