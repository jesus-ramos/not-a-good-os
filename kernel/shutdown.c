/**
 * @file
 *
 * Shutdown related code
 */

#include <asm/common.h>
#include <asm/shutdown.h>

#include <kernel/stdio.h>

void shutdown()
{
    printk("Shutting down kernel\n");

    arch_halt();
}
