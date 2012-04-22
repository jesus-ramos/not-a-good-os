#include <kernel/screen.h>

#include <asm/desc_tables.h>

void kinit()
{
    fb_clear();
    init_descriptor_tables();
}

int kmain(void *mbd, unsigned int magic)
{
    if (magic != 0x2BADB002)
    {
        fb_put_str("BAD MAGIC VALUE FROM LOADER!!! PANIC!!!");
        return 0xDEADBEEF;
    }

    kinit();

    fb_put_str("Yep still boots, now with interrupts :)\n");

    asm volatile ("int $0x3");
    asm volatile ("int $0x4");

    return 0;
}
