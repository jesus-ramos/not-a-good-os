#ifndef _ASM_COMMON_H
#define _ASM_COMMON_H

#include <kernel/types.h>

static inline void outportb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" :  : "dN" (port), "a" (value));
}

static inline uint8_t inportb(uint16_t port)
{
    uint8_t ret;

    asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));

    return ret;
}

static inline uint16_t inportw(uint16_t port)
{
    uint16_t ret;

    asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));

    return ret;
}

static inline void io_wait()
{
    asm volatile ("jmp 1f\n\t"
                  "1: jmp 1f\n\t"
                  "2:");

}

static inline int get_cpu_flags()
{
    int flags;

    asm volatile ("pushf\n\t"
                  "popl %0"
                  : "=g" (flags));

    return flags;
}

static inline unsigned long read_esp()
{
    unsigned long esp;

    asm volatile ("mov %%esp, %0" : "=r" (esp));

    return esp;
}

static inline unsigned long read_ebp()
{
    unsigned long ebp;

    asm volatile ("mov %%ebp, %0" : "=r" (ebp));

    return ebp;
}

static inline void disable_interrupts()
{
    asm volatile ("cli");
}

static inline void enable_interrupts()
{
    asm volatile ("sti");
}

/* process.s */
extern unsigned long read_eip();

#endif /* _ASM_COMMON_H */
