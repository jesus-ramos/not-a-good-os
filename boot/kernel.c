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

extern int __kernel_start;
extern int __kernel_end;
unsigned long kernel_start_addr = (unsigned long)&__kernel_start;
unsigned long kernel_end_addr = (unsigned long)&__kernel_end;

/**
 * @brief Main initialization function for the kernel, all initialization should
 * be done here
 *
 * @param[in] mbd pointer to the multiboot info struct
 *
 * Any initialization that fails in this function should just PANIC() as most of
 * this is pretty important stuff
 */
void kinit(const struct multiboot_info *mbd)
{
    /* This includes memory occupied by the kernel */
    unsigned long avail_mem_mb = mbd->mem_upper / 1024;

    init_console();

    printk("Loaded kernel from address 0x%X to address 0x%X\n",
           kernel_start_addr, kernel_end_addr);
    printk("Available memory %uMB\n", avail_mem_mb);

    init_descriptor_tables();
    setup_cpu_exception_handling();
    /* init_paging(); */
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
int kmain(const struct multiboot_info *mbd, unsigned int magic)
{
    /* Initialize the VGA display first to clear the screen */
    vga_init();

    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
        PANIC("Received bad magic value from bootloader!!!");

    if (!mbd->flags & MULTIBOOT_INFO_MEMORY)
        PANIC("Could not determine memory size");

    kinit(mbd);

    while (1);

    return 0;
}
