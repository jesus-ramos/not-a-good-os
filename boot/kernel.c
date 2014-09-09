/**
 * @file
 *
 * This is the main entry point into the kernel after the bootloader has handed
 * control to our loader and simple initialization has completed
 */

#include <kernel/console.h>
#include <kernel/keyboard.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/scheduler.h>
#include <kernel/screen.h>
#include <kernel/stdio.h>
#include <kernel/timer.h>

#include <asm/common.h>
#include <asm/desc_tables.h>

#include "multiboot.h"

unsigned long total_mem;

/**
 * @brief Main initialization function for the kernel, all initialization should
 * be done here
 */
void kinit()
{
    init_console();
    init_descriptor_tables();
    init_paging();
    init_keyboard();
    init_timer(SCHED_TICK);

    enable_interrupts();
}

/**
 * @brief Main entry point into the kernel
 *
 * @param[in] mbd data from the multiboot format to determine memory size
 * @param magic value from the bootloader to check for corruption and correct
 * bootloader
 *
 * @return This function should never return
 */
int kmain(struct multiboot_info *mbd, unsigned int magic)
{
    /* Initialize the VGA display first to clear the screen */
    vga_init();

    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
        PANIC("Received bad magic value from bootloader!!!");

    if (mbd->flags & MULTIBOOT_INFO_MEMORY)
    {
        total_mem = mbd->mem_lower + mbd->mem_upper;
        mem_end = total_mem * 1024;
        printk("Booting with: %u kb of memory\n", total_mem);
    }
    else
        PANIC("Could not determine memory size");

    kinit();

    while (1);

    return 0;
}
