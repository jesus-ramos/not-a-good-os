#include <kernel/console.h>
#include <kernel/keyboard.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/screen.h>
#include <kernel/stdio.h>

#include <asm/common.h>
#include <asm/desc_tables.h>

#include "multiboot.h"

unsigned long total_mem;

int kinit()
{
    init_descriptor_tables();
    init_paging();
    init_keyboard();
    init_console();
    
    enable_interrupts();
    
    return 0;
}

int kmain(struct multiboot_info *mbd, unsigned int magic)
{
    fb_clear();
    
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
        PANIC("BAD MAGIC VALUE FROM BOOTLOADER!!!");

    if (mbd->flags & MULTIBOOT_INFO_MEMORY)
    {
        total_mem = mbd->mem_lower + mbd->mem_upper;
        printk("Booting with: %u kb of memory\n", total_mem);
    }
    else
        PANIC("Could not determine memory size\n");
    
    kinit();

    while (1);

    return 0;
}
