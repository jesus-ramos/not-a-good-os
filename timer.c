#include <kernel/stdio.h>
#include <kernel/timer.h>

#include <asm/common.h>
#include <asm/interrupt.h>

#define TIMER_IRQ IRQ0

uint32_t tick = 0;

void timer_tick(struct registers *regs)
{
    tick++;
    printk("TIMER TICK: %u\n", tick);
}

void init_timer(uint32_t freq)
{
    uint32_t div;
    uint8_t low;
    uint8_t high;
    
    register_interrupt_handler(TIMER_IRQ, timer_tick);

    div = 1193180 / freq;
    
    outportb(0x43, 0x36);

    low = (uint8_t)(div & 0xFF);
    high = (uint8_t)((div >> 8) & 0xFF);

    outportb(0x40, low);
    outportb(0x40, high);
}
