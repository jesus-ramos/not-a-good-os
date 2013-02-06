/**
 * @file
 *
 * Dynamic memory allocation implementation
 */

#include <kernel/heap.h>
#include <kernel/paging.h>

#define ALIGN     0xFFFFF000
#define ALIGN_INC PAGE_SIZE

/* linker.ld */
extern unsigned int end;
unsigned long alloc_addr = (unsigned long)&end;

/**
 * @brief internal function for kmalloc() functions depending on alignment or
 * requirement of physical address
 *
 * @param size size of the requested allocation in bytes
 * @param align whether memory alignment is required
 * @param[out] phys_addr if a physical address is required then this will set the
 * value of that address
 *
 * @return a pointer to a memory location of at least size bytes optionally
 * aligned
 */
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

/**
 * @brief Function to request aligned memory
 *
 * @param size size of the requested allocation in bytes
 *
 * @return a pointer to a memory location of at least size bytes that is aligned
 */
void *kmalloc_aligned(size_t size)
{
    return _kmalloc(size, 1, NULL);
}

/**
 * @brief Function to request memory along with the physical address (required
 * for CPU specific pointers)
 *
 * @param size size of the requested allocation in bytes
 * @param[out] phys_addr physical address of the allocation
 *
 * @return a pointer to a memory location of at least size bytes and it's
 * corresponding physical address
 */
void *kmalloc_phys(size_t size, unsigned long *phys_addr)
{
    return _kmalloc(size, 0, phys_addr);
}

/**
 * @brief Function to request both aligned memory and its physical address
 *
 * @param size size of the requested allocation in bytes
 * @param[out] phys_addr the physical address of the allocation
 *
 * @return a pointer to a memory location of at least size bytes and it's
 * corresponding physical address that is correctly aligned
 */
void *kmalloc_align_phys(size_t size, unsigned long *phys_addr)
{
    return _kmalloc(size, 1, phys_addr);
}

/**
 * @brief Function to request memory
 *
 * @param size size of the requested allocation in bytes
 *
 * @return a pointer to a memory location of at least size bytes
 */
void *kmalloc(size_t size)
{
    return _kmalloc(size, 0, 0);
}

/**
 * @brief Release dynamically allocated memory
 *
 * @param[in] addr pointer to the address which to free
 *
 * @todo actually implement this
 */
void kfree(void *addr)
{

}
