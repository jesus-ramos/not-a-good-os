#ifndef _ASM_PAGING_H
#define _ASM_PAGING_H

#include <kernel/types.h>

#define ENABLE_PAGING_FLAG 0x80000000

static inline uint32_t get_faulting_address()
{
    uint32_t faulting_address;
    
    asm volatile ("mov %%cr2, %0" : "=r" (faulting_address));

    return faulting_address;
}

static inline void enable_paging()
{
    uint32_t cr0;

    asm volatile ("mov %%cr0, %0" : "=r" (cr0));
    cr0 |= ENABLE_PAGING_FLAG;
    asm volatile ("mov %0, %%cr0" : : "r" (cr0));
}

static inline void switch_page_directory(struct page_directory *page_dir)
{
    asm volatile ("mov %0, %%cr3" : : "r" (&page_dir->tables_physical));
    enable_paging();
}

#endif /* _ASM_PAGING_H */
