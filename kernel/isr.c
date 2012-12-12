#include <kernel/stdio.h>

#include <asm/common.h>
#include <asm/desc_tables.h>
#include <asm/interrupt.h>

isr_t interrupt_handlers[256];

void isr_handler(struct registers regs)
{
    isr_t handler;

    if (interrupt_handlers[regs.int_num])
    {
        handler = interrupt_handlers[regs.int_num];
        handler(&regs);
    }
}

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

void register_interrupt_handler(uint8_t num, isr_t handler)
{
    if (interrupt_handlers[num])
        printk("Overriding interrupt handler %d\n", num);
    interrupt_handlers[num] = handler;
}

void clear_interrupt(uint8_t num)
{
    interrupt_handlers[num] = NULL;
}
