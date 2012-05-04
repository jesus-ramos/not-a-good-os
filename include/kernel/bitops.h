#ifndef _BITOPS_H
#define _BITOPS_H

#include <kernel/types.h>

static inline void toggle_bitb(uint8_t *val, uint8_t bit)
{
    *val ^= (1UL << bit);
}

static inline void set_bitb(uint8_t *val, uint8_t bit)
{
    *val |= (1UL << bit);
}

static inline void unset_bitb(uint8_t *val, uint8_t bit)
{
    *val &= ~(1UL << bit);
}

static inline int check_bitb(uint8_t *val, uint8_t bit)
{
    return *val & (1UL << bit);
}

#endif /* _BITOPS_H */
