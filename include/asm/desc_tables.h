#ifndef _DESC_TABLES_H
#define _DESC_TABLES_H

#include <kernel/types.h>

/**
 * @brief Gloabl Descriptor Table Entry
 */
struct gdt_entry
{
    uint16_t limit_low; /**< Low byte of limit */
    uint16_t base_low; /**< Low byte of base */
    uint8_t  base_middle; /**< Middle byte of base */
    uint8_t  access; /**< Access flags */
    uint8_t  granularity; /**< Granularity bit (bytes or pages) */
    uint8_t  base_high; /**< High byte of base */
}__attribute__((packed));

/**
 * @brief Global Descriptor Table Pointer
 */
struct gdt_ptr
{
    uint16_t limit; /**< Limit value for the GDT */
    uint32_t base; /**< Base value for the GDT */
}__attribute__((packed));

/**
 * @brief Interrupt Descriptor Table Entry
 */
struct idt_entry
{
    uint16_t base_low; /**< Low byte of base */
    uint16_t selector; /**< Code segment selector in GDT or LDT */
    uint8_t  zero; /**< UNUSED, always set to zero */
    uint8_t  flags; /**< Type and attributes flags */
    uint16_t base_high; /**< High byte of base */
}__attribute__((packed));

/**
 * @brief Interrupt Descriptor Table Pointer
 */
struct idt_ptr
{
    uint16_t limit; /**< Limit value for the IDT */
    uint32_t base; /**< Base value for the IDT */
}__attribute__((packed));

void init_descriptor_tables();

#define MASTER 0x20
#define SLAVE  0xA0

/**
 * @brief Macro used to define Intterupt Service Routine handlers
 *
 * @param num ISR number
 */
#define DEF_ISR(num) extern void isr##num()

/**
 * @brief Macro used to define Interrupt Request handlers
 *
 * @param num IRQ number
 */
#define DEF_IRQ(num) extern void irq##num()

DEF_ISR(0);
DEF_ISR(1);
DEF_ISR(2);
DEF_ISR(3);
DEF_ISR(4);
DEF_ISR(5);
DEF_ISR(6);
DEF_ISR(7);
DEF_ISR(8);
DEF_ISR(9);
DEF_ISR(10);
DEF_ISR(11);
DEF_ISR(12);
DEF_ISR(13);
DEF_ISR(14);
DEF_ISR(15);
DEF_ISR(16);
DEF_ISR(17);
DEF_ISR(18);
DEF_ISR(19);
DEF_ISR(20);
DEF_ISR(21);
DEF_ISR(22);
DEF_ISR(23);
DEF_ISR(24);
DEF_ISR(25);
DEF_ISR(26);
DEF_ISR(27);
DEF_ISR(28);
DEF_ISR(29);
DEF_ISR(30);
DEF_ISR(31);

DEF_IRQ(0);
DEF_IRQ(1);
DEF_IRQ(2);
DEF_IRQ(3);
DEF_IRQ(4);
DEF_IRQ(5);
DEF_IRQ(6);
DEF_IRQ(7);
DEF_IRQ(8);
DEF_IRQ(8);
DEF_IRQ(9);
DEF_IRQ(10);
DEF_IRQ(11);
DEF_IRQ(12);
DEF_IRQ(13);
DEF_IRQ(14);
DEF_IRQ(15);

#endif /* _DESC_TABLES_H */
