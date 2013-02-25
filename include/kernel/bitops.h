#ifndef _BITOPS_H
#define _BITOPS_H

#include <kernel/types.h>

/**
 * @brief Toggles a bit in a byte
 *
 * @parma[out] val pointer to the byte which has the bit to be toggled
 * @param bit the bit index to toggle
 */
static inline void toggle_bitb(uint8_t *val, uint8_t bit)
{
    *val ^= (1UL << bit);
}

/**
 * @brief Sets a bit in a byte
 *
 * @param[out] val pointer to the byte which has the bit to be set
 * @param bit the bit index to set
 */
static inline void set_bitb(uint8_t *val, uint8_t bit)
{
    *val |= (1UL << bit);
}

/**
 * @brief Unsets a bit in a byte
 *
 * @param[out] val pointer to the byte which has the bit to be unset
 * @param bit the bit index to unset
 */
static inline void unset_bitb(uint8_t *val, uint8_t bit)
{
    *val &= ~(1UL << bit);
}

/**
 * @brief Checks if a bit in a byte is set
 *
 * @param[in] val pointer to the byte which you want to check a bit index for
 * @param bit the bit index to check
 *
 * @return 1 if the bit is set in val, 0 otherwise
 */
static inline int check_bitb(uint8_t *val, uint8_t bit)
{
    return *val & (1UL << bit);
}

#endif /* _BITOPS_H */
