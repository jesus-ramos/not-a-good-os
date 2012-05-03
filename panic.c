#include <kernel/panic.h>
#include <kernel/stdio.h>

#include <asm/asm_common.h>

void panic(const char *message, const char *file_name, unsigned int line_num)
{
    disable_interrupts();

    printk("PANIC!! %s at %s : line %d.\n", message, file_name, line_num);

    while (1);
}

void bug(const char *message, const char *file_name, unsigned int line_num)
{
    printk("BUG: %s at %s : line %d.\n", message, file_name, line_num);
}
