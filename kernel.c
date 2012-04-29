#include <kernel/screen.h>
#include <kernel/stdio.h>
#include <kernel/timer.h>

#include <asm/asm_common.h>
#include <asm/desc_tables.h>

int kinit()
{
    fb_clear();
    init_descriptor_tables();
    enable_interrupts();
    
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

    printk("This %d string is awesome %s\n", 123, "testing string");

    while (1);
    
    return 0;
}
