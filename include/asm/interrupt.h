#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include <kernel/types.h>

#include <asm/asm_common.h>
#include <asm/port_comm.h>

#define IRQ_ENABLED_FLAG (1 << 9)

#define IRQ0  32
#define IRQ1  33
#define IRQ2  34
#define IRQ3  35
#define IRQ4  36
#define IRQ5  37
#define IRQ6  38
#define IRQ7  39
#define IRQ8  40
#define IRQ9  41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

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

    uint32_t int_num;
    uint32_t err;

    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t user_esp;
    uint32_t ss;
};

typedef void (*isr_t)(struct registers *);

void register_interrupt_handler(uint8_t num, isr_t handler);

extern isr_t interrupt_handlers[];

static inline int irq_enabled()
{
    return get_cpu_flags() & IRQ_ENABLED_FLAG;
}

static inline void send_eoi()
{
    outportb(0x20, 0x20);
}

#endif /* _INTERRUPT_H */
