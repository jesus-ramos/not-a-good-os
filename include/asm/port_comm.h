#ifndef _PORT_COMM_H
#define _PORT_COMM_H

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

#endif /* _PORT_COMM_H */
