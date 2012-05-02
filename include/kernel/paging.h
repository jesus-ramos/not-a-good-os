#ifndef _PAGING_H
#define _PAGING_H

#include <kernel/types.h>

#define PAGE_SIZE 4096

#define PAGE_FAULT_IRQ IRQ14

#define PAGE_PRESENT_FAULT_FLAG     (1 << 0)
#define WRITE_FAULT_FLAG            (1 << 1)
#define USER_MODE_FAULT_FLAG        (1 << 2)
#define INVALID_RESERVED_FAULT_FLAG (1 << 3)
#define INSN_FETCH_FAULT_FLAG       (1 << 4)

struct page
{
    uint32_t present       : 1;
    uint32_t rw            : 1;
    uint32_t user          : 1;
    uint32_t accessed      : 1;
    uint32_t dirty         : 1;
    uint32_t reserved      : 7; /* DO NOT TOUCH! */
    uint32_t frame_address : 20;
};

struct page_table
{
    struct page pages[1024];
};

struct page_directory
{
    struct page_table *page_tables[1024];
    uint32_t tables_physical[1024];
    uint32_t physical;
};

void init_paging();

#endif /* _PAGING_H */
