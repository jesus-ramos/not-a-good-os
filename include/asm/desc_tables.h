#ifndef _DESC_TABLES_H
#define _DESC_TABLES_H

#include <kernel/types.h>

struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
}__attribute__((packed));

struct gdt_ptr
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

struct idt_entry
{
    uint16_t base_low;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  flags;
    uint16_t base_high;
}__attribute__((packed));

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed));

void init_descriptor_tables();

#define MASTER 0x20
#define SLAVE  0xA0

#define DEF_ISR(num) extern void isr##num()
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
