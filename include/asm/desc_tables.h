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

typedef struct gdt_entry gdt_entry_t;
typedef struct gdt_ptr   gdt_ptr_t;
typedef struct idt_entry idt_entry_t;
typedef struct idt_ptr   idt_ptr_t;

void init_descriptor_tables();

/* ISR's */
#define DEF_ISR(num) extern void isr##num()

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

#undef DEF_ISR

#endif /* _DESC_TABLES_H */
