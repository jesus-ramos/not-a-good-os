#ifndef _PAGING_H
#define _PAGING_H

#include <kernel/types.h>

#define PAGE_SIZE 4096

#define PAGE_FAULT_IRQ 14

#define PAGE_PRESENT_FAULT_FLAG     (1 << 0)
#define WRITE_FAULT_FLAG            (1 << 1)
#define USER_MODE_FAULT_FLAG        (1 << 2)
#define INVALID_RESERVED_FAULT_FLAG (1 << 3)
#define INSN_FETCH_FAULT_FLAG       (1 << 4)

struct page
{
    int present       : 1;
    int rw            : 1;
    int user          : 1;
    int accessed      : 1;
    int dirty         : 1;
    int reserved      : 7; /* DO NOT TOUCH! */
    int frame         : 20;
};

struct page_table
{
    struct page pages[1024];
};

struct page_directory
{
    struct page_table *page_tables[1024];
    unsigned long tables_physical[1024];
    unsigned long physical;
};

void init_paging();
struct page *get_page(unsigned long address, int make, struct page_directory *page_directory);

extern unsigned long total_mem;
extern unsigned long mem_end;

#endif /* _PAGING_H */
