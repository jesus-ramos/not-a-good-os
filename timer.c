#include <kernel/stdio.h>
#include <kernel/timer.h>

#include <asm/interrupt.h>
#include <asm/port_comm.h>

uint32_t tick = 0;

void timer_callback(struct registers *regs)
{
    tick++;
    printk("TIMER TICK: %u\n", tick);
}

void init_timer(uint32_t freq)
{
    uint32_t div;
    uint8_t low;
    uint8_t high;
    
    register_interrupt_handler(IRQ0, timer_callback);

    div = 1193180 / freq;
    
    outportb(0x43, 0x36);

    low = (uint8_t)(div & 0xFF);
    high = (uint8_t)((div >> 8) & 0xFF);

    outportb(0x40, low);
    outportb(0x40, high);
}
