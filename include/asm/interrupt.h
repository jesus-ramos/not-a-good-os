#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include <kernel/types.h>

#include <asm/common.h>

#define IRQ_ENABLED_FLAG (1 << 9)

struct registers
{
    uint32_t ds;
    
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;

    uint32_t isr_num;
    uint32_t err;

    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t useresp;
    uint32_t ss;
};

static inline int irq_enabled()
{
    return get_cpu_flags() & IRQ_ENABLED_FLAG;
}

#endif /* _INTERRUPT_H */
