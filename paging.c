#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/stdio.h>

#include <asm/paging.h>
#include <asm/interrupt.h>

void handle_page_fault(struct registers *regs)
{
    unsigned long address;

    address = get_faulting_address();

    printk("Page fault\n"
           "Address: %lu\n"
           "Flags: 0x%X\n",
           address, regs->err);
    PANIC("PAGING NOT IMPLEMENTED YET");
}

void init_paging()
{
    register_interrupt_handler(PAGE_FAULT_IRQ, handle_page_fault);
}
