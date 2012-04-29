#include <kernel/stdio.h>

#include <asm/desc_tables.h>
#include <asm/interrupt.h>
#include <asm/port_comm.h>

isr_t interrupt_handlers[256];

void isr_handler(struct registers regs)
{
    isr_t handler;
    
    printk("Received interrupt: %u\n", regs.int_num);

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
    interrupt_handlers[num] = handler;
}
