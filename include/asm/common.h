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

#endif /* _ASM_COMMON_H */
