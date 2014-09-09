#ifndef _HEAP_H
#define _HEAP_H

#include <kernel/types.h>

void *kmalloc(size_t size);
void *kmalloc_aligned(size_t size);
void *kmalloc_phys(size_t size, unsigned long *phys_addr);
void *kmalloc_align_phys(size_t size, unsigned long *phys_addr);
void kfree(void *addr);

#endif /* _HEAP_H */
