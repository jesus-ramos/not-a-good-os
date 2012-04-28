#include <kernel/screen.h>
#include <kernel/string.h>
#include <kernel/timer.h>

#include <asm/desc_tables.h>

int kinit()
{
    fb_clear();
    init_descriptor_tables();

    asm volatile ("sti");
    
    return 0;
}

int kmain(void *mbd, unsigned int magic)
{
    if (magic != 0x2BADB002)
    {
        fb_put_str("BAD MAGIC VALUE FROM LOADER!!! PANIC!!!");
        return 0xDEADBEEF;
    }

    kinit();
    
    init_timer(50);

    while (1);

    return 0;
}
