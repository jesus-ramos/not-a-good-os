#include <kernel/screen.h>

#include <asm/interrupt.h>

void isr_handler(struct registers regs)
{
    fb_put_str("received interrupt\n");
}
