#include <kernel/stdio.h>

#include <asm/common.h>
#include <asm/desc_tables.h>
#include <asm/interrupt.h>

isr_t interrupt_handlers[256];

/**
 * @brief The main handler for any interrupt service routine
 *
 * @param regs register status at the time of the interrupt
 */
void isr_handler(struct registers regs)
{
    isr_t handler;

    if (interrupt_handlers[regs.int_num])
    {
        handler = interrupt_handlers[regs.int_num];
        handler(&regs);
    }
}

/**
 * @brief The main handler for any interrupt request
 *
 * @param regs register status at the time of the interrupt
 */
void irq_handler(struct registers regs)
{
    isr_t handler;

    if (regs.int_num >= 40)
        outportb(SLAVE, 0x20);
    outportb(MASTER, 0x20);

    if (interrupt_handlers[regs.int_num])
    {
        handler = interrupt_handlers[regs.int_num];
        handler(&regs);
    }
}

/**
 * @brief Set the handler for the appropriate interrupt
 *
 * @param num the interrupt number to handle
 * @param handler the handler function to execute when the interrupt happens
 */
void register_interrupt_handler(uint8_t num, isr_t handler)
{
    if (interrupt_handlers[num])
        printk("Overriding interrupt handler %d\n", num);
    interrupt_handlers[num] = handler;
}

/**
 * @brief Clear the interrupt handler for a particular interrupt
 *
 * @param num the interrupt number which we want to clear the handler for
 */
void clear_interrupt(uint8_t num)
{
    interrupt_handlers[num] = NULL;
}
