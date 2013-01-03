#include <kernel/heap.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/stdio.h>
#include <kernel/string.h>

#include <asm/paging.h>
#include <asm/interrupt.h>

#define INDEX_FROM_BIT(b) (b / (8 * sizeof(unsigned long)))
#define OFFSET_FROM_BIT(b) (b % (8 * sizeof(unsigned long)))

unsigned long *frames;
unsigned long num_frames;

unsigned long mem_end;

struct page_directory *kernel_directory;
struct page_directory *current_directory;

extern unsigned long alloc_addr;

/* process.s */
extern void copy_page_physical(unsigned long src_addr,
                               unsigned long dest_address);

static inline void get_fid(unsigned long frame_addr, int *frame, int *index,
                           int *offset)
{
    *frame = frame_addr / PAGE_SIZE;
    *index = INDEX_FROM_BIT(*frame);
    *offset = OFFSET_FROM_BIT(*frame);
}

static void set_frame(unsigned long frame_addr)
{
    int frame;
    int index;
    int offset;

    get_fid(frame_addr, &frame, &index, &offset);
    frames[index] |= (0x1 << offset);
}

static void clear_frame(unsigned long frame_addr)
{
    int frame;
    int index;
    int offset;

    get_fid(frame_addr, &frame, &index, &offset);
    frames[index] &= ~(0x1 << offset);
}

/* static int test_frame(unsigned long frame_addr) */
/* { */
/*     int frame; */
/*     int index; */
/*     int offset; */

/*     get_fid(frame_addr, &frame, &index, &offset); */
/*     return frames[index] & (0x1 << offset); */
/* } */

static unsigned long first_free_frame()
{
    int i, j;
    int test;

    for (i = 0; i < INDEX_FROM_BIT(num_frames); i++)
        if (frames[i] != 0xFFFFFFFF)
            for (j = 0; j < sizeof(unsigned long) * 8; j++)
            {
                test = 1 << j;
                if (!(frames[i] & test))
                    return i * sizeof(unsigned long) * 8 + j;
            }

    return -1;
}

void alloc_frame(struct page *page, int kernel, int write)
{
    unsigned long index;

    if (!page || page->frame)
        return;

    index = first_free_frame();
    if (index == (unsigned long)-1)
        PANIC("Frame allocation failed");

    set_frame(index * PAGE_SIZE);
    page->present = 1;
    page->rw = (write) ? 1 : 0;
    page->user = (kernel) ? 0 : 1;
    page->frame = index;
}

void free_frame(struct page *page)
{
    if (!page->frame)
        return;

    clear_frame(page->frame);
    page->frame = 0;
}

void handle_page_fault(struct registers *regs)
{
    unsigned long address;

    address = get_faulting_address();

    printk("Page fault\n"
           "Address: %u\n"
           "Flags: 0x%X\n",
           address, regs->err);
    PANIC("PAGING NOT IMPLEMENTED YET");
}

struct page *get_page(unsigned long address, int make,
                      struct page_directory *page_directory)
{
    unsigned long table_index;
    unsigned long tmp;

    address /= PAGE_SIZE;
    table_index = address / 1024;

    if (page_directory->page_tables[table_index])
        return
            &page_directory->page_tables[table_index]->pages[address % 1024];

    if (make)
    {
        page_directory->page_tables[table_index] = (struct page_table *)
            kmalloc_align_phys(sizeof(struct page_table), &tmp);
        memset(page_directory->page_tables[table_index], 0, PAGE_SIZE);
        page_directory->tables_physical[table_index] = tmp | 0x7;

        return
            &page_directory->page_tables[table_index]->pages[address % 1024];
    }

    return NULL;
}

static struct page_table *clone_table(struct page_table *src,
                                      unsigned long *phys_addr)
{
    struct page_table *table;
    int i;

    table = (struct page_table *)
        kmalloc_align_phys(sizeof(struct page_table), phys_addr);
    memset(table, 0, sizeof(struct page_table));

    for (i = 0; i < 1024; i++)
        if (src->pages[i].frame)
        {
            alloc_frame(&table->pages[i], 0, 0);
            table->pages[i].present  = src->pages[i].present;
            table->pages[i].rw       = src->pages[i].rw;
            table->pages[i].user     = src->pages[i].user;
            table->pages[i].accessed = src->pages[i].accessed;
            table->pages[i].dirty    = src->pages[i].dirty;
            copy_page_physical(src->pages[i].frame * PAGE_SIZE,
                               table->pages[i].frame * PAGE_SIZE);
        }

    return table;
}

struct page_directory *clone_directory(struct page_directory *src)
{
    unsigned long phys_addr;
    struct page_directory *page_dir;
    unsigned long offset;
    int i;
    unsigned long phys;

    page_dir = (struct page_directory *)
        kmalloc_align_phys(sizeof(struct page_directory), &phys_addr);
    memset(page_dir, 0, sizeof(struct page_directory));
    offset = (unsigned long)page_dir->tables_physical -
        (unsigned long)page_dir;
    page_dir->physical = phys_addr + offset;

    for (i = 0; i < 1024; i++)
    {
        if (!src->page_tables[i])
            continue;

        if (kernel_directory->page_tables[i] == src->page_tables[i])
        {
            page_dir->page_tables[i]          = src->page_tables[i];
            page_dir->tables_physical[i] = src->tables_physical[i];
        }
        else
        {
            page_dir->page_tables[i] = clone_table(src->page_tables[i],
                                                   &phys);
            page_dir->tables_physical[i] = phys | 0x07;
        }
    }

    return page_dir;
}

void init_paging()
{
    int size;
    int i;

    num_frames = mem_end / PAGE_SIZE;
    size = INDEX_FROM_BIT(num_frames);
    frames = (unsigned long *)kmalloc(size);
    memset(frames, 0, size);

    kernel_directory = (struct page_directory *)
        kmalloc_aligned(sizeof(struct page_directory));
    memset(kernel_directory, 0, sizeof(struct page_directory));
    current_directory = kernel_directory;

    i = 0;
    while (i < alloc_addr)
    {
        alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
        i += PAGE_SIZE;
    }

    register_interrupt_handler(PAGE_FAULT_IRQ, handle_page_fault);

    switch_page_directory(kernel_directory);
}
