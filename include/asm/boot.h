#ifndef _ASM_BOOT_H
#define _ASM_BOOT_H

#include <kernel/types.h>

/* 32 bit address type for x86 */
typedef unsigned int addr_t;

/* Functions for use with the segment registers */

/**
 * @brief Set the value of the FS (general purpose) segment register
 *
 * @param segment value to set to FS
 */
static inline void set_fs(uint16_t segment)
{
    asm volatile ("movw %0, %%fs" : : "rm" (segment));
}

/**
 * @brief Set the value of the GS (general purpose) segment register
 *
 * @param segment value to set to GS
 */
static inline void set_gs(uint16_t segment)
{
    asm volatile ("movw %0, %%gs" : : "rm" (segment));
}

static inline uint32_t read_fs32(addr_t address)
{
    uint32_t value;

    asm volatile ("movl %%fs:%1, %0" :
                  "=r" (value) : "m" (*(uint32_t *)address));

    return value;
}

static inline void set_fs32(uint32_t value, addr_t address)
{
    asm volatile ("movl %1, %%fs:%0" :
                  "+m" (*(uint32_t *)address) : "ri" (value));
}

static inline uint32_t read_gs32(addr_t address)
{
    uint32_t value;

    asm volatile ("movl %%gs:%1, %0" :
                  "=r" (value) : "m" (*(uint32_t *)address));

    return value;
}

#define DELAY_PORT 0x80

static inline void io_delay()
{
    asm volatile ("outb %%al, %0" : : "dN" (DELAY_PORT));
}

int enable_a20_line();
/* biosint.s */
void bios_call_interrupt(uint8_t interrupt_no,
                         const struct bios_registers *in_registers,
                         struct bios_registers *out_registers);

#endif /* _ASM_BOOT_H */
