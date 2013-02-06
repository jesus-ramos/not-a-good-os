/**
 * @file
 *
 * Hardware timer implementation
 */

#include <kernel/scheduler.h>
#include <kernel/stdio.h>
#include <kernel/timer.h>

#include <asm/common.h>
#include <asm/interrupt.h>

#define TIMER_IRQ IRQ0

uint32_t tick = 0;

/**
 * @brief Timer handler function that is called after every "tick"
 *
 * @param[in] regs register status at the time of the tick
 */
void timer_tick(struct registers *regs)
{
    tick++;
    schedule();
}

/**
 * @brief Timer initialization function
 *
 * @param freq the frequency at which the cpu timer should go off
 */
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
