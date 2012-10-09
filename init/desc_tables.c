#include <kernel/string.h>

#include <asm/common.h>
#include <asm/desc_tables.h>
#include <asm/interrupt.h>

/* Defined in gdt.s */
extern void gdt_flush(uint32_t gdt_ptr);
extern void idt_flush(uint32_t idt_ptr);

struct gdt_entry gdt_entries[5];
struct gdt_ptr gdt_ptr;
struct idt_entry idt_entries[256];
struct idt_ptr idt_ptr;

#define IDT_SET_GATE(isrnum) idt_set_gate(isrnum, (uint32_t)isr##isrnum, 0x08, 0x8E)
#define IDT_SET_IRQ_GATE(num, irqnum) idt_set_gate(num, (uint32_t)irq##irqnum, 0x08, 0x8E)

#define MASTER1 (MASTER + 1)
#define SLAVE1  (SLAVE + 1)

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit,
			 uint8_t access, uint8_t granularity)
{
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;
    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;
    gdt_entries[num].granularity |= granularity & 0xF0;
    gdt_entries[num].access       = access;
}

static void init_gdt()
{
    gdt_ptr.limit = (sizeof(struct gdt_entry) * 5) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);                /* Null segment */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);	/* Code segment */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);	/* Data segment */
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);	/* User mode code segment */
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);	/* User mode data segment */

    gdt_flush((uint32_t)&gdt_ptr);
}

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[num].base_low  = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].selector  = sel;
    idt_entries[num].zero      = 0;
    idt_entries[num].flags     = flags;
    /* USER MODE */
    /* idt_entries[num].flags = flags | 0x60; */
}

static void remap_irq_table()
{
    outportb(MASTER, 0x11);
    outportb(SLAVE, 0x11);
    outportb(MASTER1, 0x20);
    outportb(SLAVE1, 0x28);
    outportb(MASTER1, 0x04);
    outportb(SLAVE1, 0x02);
    outportb(MASTER1, 0x01);
    outportb(SLAVE1, 0x01);
    outportb(MASTER1, 0x00);
    outportb(SLAVE1, 0x00);
}

static void init_idt()
{
    idt_ptr.limit = sizeof(struct idt_entry) * 256 -1;
    idt_ptr.base  = (uint32_t)&idt_entries;

    memset(&idt_entries, 0, sizeof(struct idt_entry) * 256);

    remap_irq_table();

    IDT_SET_GATE(0);
    IDT_SET_GATE(1);
    IDT_SET_GATE(2);
    IDT_SET_GATE(3);
    IDT_SET_GATE(4);
    IDT_SET_GATE(5);
    IDT_SET_GATE(6);
    IDT_SET_GATE(7);
    IDT_SET_GATE(8);
    IDT_SET_GATE(9);
    IDT_SET_GATE(10);
    IDT_SET_GATE(11);
    IDT_SET_GATE(12);
    IDT_SET_GATE(13);
    IDT_SET_GATE(14);
    IDT_SET_GATE(15);
    IDT_SET_GATE(16);
    IDT_SET_GATE(17);
    IDT_SET_GATE(18);
    IDT_SET_GATE(19);
    IDT_SET_GATE(20);
    IDT_SET_GATE(21);
    IDT_SET_GATE(22);
    IDT_SET_GATE(23);
    IDT_SET_GATE(24);
    IDT_SET_GATE(25);
    IDT_SET_GATE(26);
    IDT_SET_GATE(27);
    IDT_SET_GATE(28);
    IDT_SET_GATE(29);
    IDT_SET_GATE(30);
    IDT_SET_GATE(31);

    IDT_SET_IRQ_GATE(32, 0);
    IDT_SET_IRQ_GATE(33, 1);
    IDT_SET_IRQ_GATE(34, 2);
    IDT_SET_IRQ_GATE(35, 3);
    IDT_SET_IRQ_GATE(36, 4);
    IDT_SET_IRQ_GATE(37, 5);
    IDT_SET_IRQ_GATE(38, 6);
    IDT_SET_IRQ_GATE(39, 7);
    IDT_SET_IRQ_GATE(40, 8);
    IDT_SET_IRQ_GATE(41, 9);
    IDT_SET_IRQ_GATE(42, 10);
    IDT_SET_IRQ_GATE(43, 11);
    IDT_SET_IRQ_GATE(44, 12);
    IDT_SET_IRQ_GATE(45, 13);
    IDT_SET_IRQ_GATE(46, 14);
    IDT_SET_IRQ_GATE(47, 15);

    idt_flush((uint32_t)&idt_ptr);
}

void init_descriptor_tables()
{
    init_gdt();
    init_idt();

    memset(&interrupt_handlers, 0, sizeof(isr_t) * 256);
}
