#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include <kernel/types.h>

#include <asm/common.h>

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

/**
 * @brief CPU Register State for use in interrupt handlers
 */
struct registers
{
    uint32_t ds;                /**< Data segment register */
    uint32_t edi;               /**< Destination Index register for string
                                 * operations */
    uint32_t esi;               /**< Source Index register for string
                                 * operations */
    uint32_t ebp;               /**< Stack Base Pointer register */
    uint32_t esp;               /**< Stack Pointer register */
    uint32_t ebx;               /**< Base Index register used for arrays */
    uint32_t edx;               /**< General data register */
    uint32_t ecx;               /**< Counter register */
    uint32_t eax;               /**< Accumulator register */
    uint32_t int_num;           /**< Interrupt number */
    uint32_t err;               /**< Exception/Error number */
    uint32_t eip;               /**< Instruction pointer register */
    uint32_t cs;                /**< Code Segment register */
    uint32_t eflags;            /**< CPU flags */
    uint32_t user_esp;          /**< User mode stack pointer register */
    uint32_t ss;                /**< Stack Segment register */
};

typedef void (*isr_t)(struct registers *);

void register_interrupt_handler(uint8_t num, isr_t handler);
void clear_intterupt(uint8_t num);

extern isr_t interrupt_handlers[];

/**
 * @brief Check if IRQ's are enabled on the executing core
 *
 * @return 1 if IRQ's are enabled, 0 otherwise
 */
static inline int irq_enabled()
{
    return get_cpu_flags() & IRQ_ENABLED_FLAG;
}

/**
 * @brief Send an EOI (End of Intterupt) to the core that caused the interrupt
 */
static inline void send_eoi()
{
    outportb(0x20, 0x20);
}

#endif /* _INTERRUPT_H */
