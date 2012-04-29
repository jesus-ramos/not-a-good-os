#ifndef _DIV_H
#define _DIV_H

#define do_div(num, base)                                       \
    ({                                                          \
        int __res;                                              \
        asm volatile ("divl %4"                                 \
                      : "=a" (num), "=d" (__res)                \
                      : "0" (num), "1" (0), "r" (base));        \
        __res;                                                  \
    })


#endif /* _DIV_H */
