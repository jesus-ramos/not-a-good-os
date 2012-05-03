#include <kernel/keyboard.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/screen.h>
#include <kernel/stdio.h>

#include <asm/asm_common.h>
#include <asm/desc_tables.h>

int kinit()
{
    fb_clear();
    init_descriptor_tables();
    init_paging();
    init_keyboard();
    enable_interrupts();
    
    return 0;
}

int kmain(void *mbd, unsigned int magic)
{
    if (magic != 0x2BADB002)
        PANIC("BAD MAGIC VALUE FROM BOOTLOADER!!!");

    kinit();
    
    while (1);
    
    return 0;
}
