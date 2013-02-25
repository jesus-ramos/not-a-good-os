#ifndef _ASM_COMMON_H
#define _ASM_COMMON_H

#include <kernel/types.h>

/**
 * @brief Writes a byte to a port
 *
 * @param port the port to write the byte to
 * @param value the value to write
 */
static inline void outportb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" :  : "dN" (port), "a" (value));
}

/**
 * @brief Reads a byte from a port
 *
 * @param port the port to read the byte from
 *
 * @return the value read from the port
 */
static inline uint8_t inportb(uint16_t port)
{
    uint8_t ret;

    asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));

    return ret;
}

/**
 * @brief Reads 2 bytes from a port
 *
 * @param port the port to read 2 bytes from
 *
 * @return the value read from the port
 */
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

/**
 * @brief Gets the CPU flags
 *
 * @return current value of the cpu flags
 */
static inline int get_cpu_flags()
{
    int flags;

    asm volatile ("pushf\n\t"
                  "popl %0"
                  : "=g" (flags));

    return flags;
}

/**
 * @brief Read the ESP(stack pointer) register
 *
 * @return value of ESP
 */
static inline unsigned long read_esp()
{
    unsigned long esp;

    asm volatile ("mov %%esp, %0" : "=r" (esp));

    return esp;
}

/**
 * @brief Read the EBP(base pointer to stack) register
 *
 * @return value of EBP
 */
static inline unsigned long read_ebp()
{
    unsigned long ebp;

    asm volatile ("mov %%ebp, %0" : "=r" (ebp));

    return ebp;
}

/* process.s */
/**
 * @brief Reads the value of the EIP(instruction pointer) register
 *
 * @return value of EIP
 */
extern unsigned long read_eip();

/**
 * @brief Disables interrupts on the executing core
 */
static inline void disable_interrupts()
{
    asm volatile ("cli");
}

/**
 * @brief Enables interrupts on the executing core
 */
static inline void enable_interrupts()
{
    asm volatile ("sti");
}

#endif /* _ASM_COMMON_H */
