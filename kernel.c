#include <kernel/screen.h>

void kinit()
{
    fb_clear();
}

int kmain(void *mbd, unsigned int magic)
{
    if (magic != 0x2BADB002)
    {
        fb_put_str("BAD MAGIC VALUE FROM LOADER!!! PANIC!!!");
        return 0xDEADBEEF;
    }

    kinit();

    fb_put_str("And so he delivered unto them framebuffer device drivers\n"
               "And it was good");

    return 0;
}
