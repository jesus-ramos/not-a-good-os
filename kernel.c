#include <kernel/screen.h>
#include <kernel/stdio.h>
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
    char buf[1024];
    
    if (magic != 0x2BADB002)
    {
        fb_put_str("BAD MAGIC VALUE FROM LOADER!!! PANIC!!!");
        return 0xDEADBEEF;
    }

    kinit();
    
    //init_timer(50);

    fb_put_str("TEST\n");

    sprintf(buf, "This %d string is awesome %s\n", 123, "testing string");

    printk("This %d string is awesome %s\n", 123, "testing string");

    fb_put_str("DOUBLE TEST\n");

    while (1);
    
    return 0;
}
