#ifndef _DIV_H
#define _DIV_H

/**
 * @brief Used to support 64 bit divides on 32 bit architectures
 */
#define do_div(num, base)                                       \
    ({                                                          \
        int __res;                                              \
        asm volatile ("divl %4"                                 \
                      : "=a" (num), "=d" (__res)                \
                      : "0" (num), "1" (0), "r" (base));        \
        __res;                                                  \
    })


#endif /* _DIV_H */
