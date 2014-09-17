#include <asm/interrupt.h>

#include <kernel/paging.h>

void setup_cpu_exception_handling()
{
    register_interrupt_handler(PAGE_FAULT, handle_page_fault);
}
