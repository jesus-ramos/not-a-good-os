#ifndef _ASM_COMMON_H
#define _ASM_COMMON_H

static inline int get_cpu_flags()
{
    int flags;

    asm volatile ("pushf\n\t"
                  "popl %0"
                  : "=g" (flags));

    return flags;
}

static inline void disable_interrupts()
{
    asm volatile ("cli");
}

static inline void enable_interrupts()
{
    asm volatile ("sti");
}

#endif /* _ASM_COMMON_H */
