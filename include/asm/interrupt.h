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

/* List of CPU Exceptions */
#define DIV_BY_ZERO 0x00
#define RESERVED1_EXCEPTION 0x01
#define NMI_INTERRUPT 0x02
#define BREAKPOINT 0x03 /* INT(3) */
#define OVERFLOW 0x04 /* INTO */
#define BOUNDS_RANGE_EXCEEDED 0x05 /* BOUND */
#define INVALID_OPCODE 0x06 /* UD2 */
#define DEVICE_NOT_AVAILABLE 0x07 /* WAIT/FWAIT */
#define DOUBLE_FAULT 0x08
#define COPROC_SEG_OVERRUN 0x09
#define INVALID_TSS 0x0A
#define SEGMENT_NOT_PRESENT 0x0B
#define STACK_SEGMENT_FAULT 0x0C
#define GENERAL_PROTECTION_FAULT 0x0D
#define PAGE_FAULT 0x0E
#define RESERVED2_EXCEPTION 0x0F
#define X87_FPU_ERROR 0x10
#define ALIGNMENT_CHECK 0x11
#define MACHINE_CHECK 0x12
#define SIMD_FP_EXCEPTION 0x13

/* List of IRQ's */
#define TIMER_IRQ IRQ0
#define KEYBOARD_IRQ IRQ1

/**
 * @brief CPU Register State for use in interrupt handlers
 */
struct registers
{
    uint32_t ds;       /**< Data segment register */
    uint32_t edi;      /**< Destination Index register for string */
                       /**< operations */
    uint32_t esi;      /**< Source Index register for string */
                       /**< operations */
    uint32_t ebp;      /**< Stack Base Pointer register */
    uint32_t esp;      /**< Stack Pointer register */
    uint32_t ebx;      /**< Base Index register used for arrays */
    uint32_t edx;      /**< General data register */
    uint32_t ecx;      /**< Counter register */
    uint32_t eax;      /**< Accumulator register */
    uint32_t int_num;  /**< Interrupt number */
    uint32_t err;      /**< Exception/Error number */
    uint32_t eip;      /**< Instruction pointer register */
    uint32_t cs;       /**< Code Segment register */
    uint32_t eflags;   /**< CPU flags */
    uint32_t user_esp; /**< User mode stack pointer register */
    uint32_t ss;       /**< Stack Segment register */
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

void setup_cpu_exception_handling();

#endif /* _INTERRUPT_H */
