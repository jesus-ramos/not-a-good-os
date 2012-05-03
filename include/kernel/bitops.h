#ifndef _BITOPS_H
#define _BITOPS_H

#include <kernel/types.h>

void toggle_bitb(uint8_t *val, uint8_t bit)
{
    *val ^= (1UL << bit);
}

#endif /* _BITOPS_H */
