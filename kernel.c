#include <kernel/screen.h>

void kinit()
{
    fb_clear();
}

void kmain(void *mbd, unsigned int magic)
{
    if (magic != 0x2BADB002)
    {
        fb_put_str("BAD MAGIC VALUE FROM LOADER!!! PANIC!!!");
        return;
    }

    kinit();
}
