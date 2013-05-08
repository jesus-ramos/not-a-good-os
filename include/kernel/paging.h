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

/**
 * @brief Virtual memory page information
 */
struct page
{
    int present       : 1;      /**< 1 if page is present in memory, 0 if just
                                 * mapped */
    int rw            : 1;      /**< Read/Write enable bit */
    int user          : 1;      /**< User access privelege bit */
    int accessed      : 1;      /**< Accessed bit, set if page has been read
                                 * from */
    int dirty         : 1;      /**< Dirty bit, set if page has been written
                                 * to */
    int reserved      : 7;      /**< Reserved bits, DO NOT TOUCH */
    int frame         : 20;     /**< Frame address of the page */
};

/**
 * @brief Page table structure
 */
struct page_table
{
    struct page pages[1024]; /**< System pages */
};

/**
 * @brief Page directory structure
 */
struct page_directory
{
    struct page_table *page_tables[1024]; /**< Page tables in the directory */
    unsigned long      tables_physical[1024]; /**< Physical addresses for the
                                               * pages */
    unsigned long      physical; /**< Physical address of the page directory */
};

void init_paging();
struct page *get_page(unsigned long address, int make,
                      struct page_directory *page_directory);
struct page_directory *clone_directory(struct page_directory *src);

extern unsigned long total_mem;
extern unsigned long mem_end;

extern struct page_directory *current_directory;

#endif /* _PAGING_H */
