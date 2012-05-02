#include <kernel/paging.h>
#include <kernel/stdio.h>

#include <asm/asm_paging.h>
#include <asm/interrupt.h>

void handle_page_fault(struct registers *regs)
{
    printk("Page fault, QUICK PANIC!!!");
}

void init_paging()
{
    register_interrupt_handler(PAGE_FAULT_IRQ, handle_page_fault);
}
