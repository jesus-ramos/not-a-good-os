#include <kernel/heap.h>
#include <kernel/paging.h>

#define ALIGN     0xFFFFF000
#define ALIGN_INC PAGE_SIZE

/* linker.ld */
extern unsigned int end;
unsigned long alloc_addr = (unsigned long)&end;

static void *_kmalloc(size_t size, int align, unsigned long *phys_addr)
{
    unsigned long tmp;

    if (align && (alloc_addr & ALIGN))
    {
        alloc_addr &= ALIGN;
        alloc_addr += ALIGN_INC;
    }
    if (phys_addr)
        *phys_addr = alloc_addr;

    tmp = alloc_addr;
    alloc_addr += size;

    return (void *)tmp;
}

void *kmalloc_aligned(size_t size)
{
    return _kmalloc(size, 1, NULL);
}

void *kmalloc_phys(size_t size, unsigned long *phys_addr)
{
    return _kmalloc(size, 0, phys_addr);
}

void *kmalloc_align_phys(size_t size, unsigned long *phys_addr)
{
    return _kmalloc(size, 1, phys_addr);
}

void *kmalloc(size_t size)
{
    return _kmalloc(size, 0, 0);
}

void kfree(void *addr)
{

}
