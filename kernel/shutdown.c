/**
 * @file
 *
 * Shutdown related code
 */

#include <asm/common.h>

#include <kernel/shutdown.h>
#include <kernel/stdio.h>

void shutdown()
{
    printk("Shutting down kernel\n");

    disable_interrupts();
    arch_halt();
}
