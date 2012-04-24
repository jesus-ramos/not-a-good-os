#include <kernel/screen.h>

#include <asm/interrupt.h>

void isr_handler(struct registers regs)
{
    fb_put_str("received interrupt: ");
    fb_put_char(regs.isr_num + '0');
    fb_put_char('\n');
}
