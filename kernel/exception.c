#include <asm/interrupt.h>

#include <kernel/paging.h>

/**
 * @brief Setup CPU exception handlers for things we care about
 */
void setup_cpu_exception_handling()
{
    register_interrupt_handler(PAGE_FAULT, handle_page_fault);
}
