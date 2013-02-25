/**
 * @file
 *
 * Definitions for atomic operations to avoid locking in certain situations
 */

#ifndef _ATOMIC_OPS_H
#define _ATOMIC_OPS_H

/**
 * @brief Atomic addition operation
 *
 * @param[out] num pointer to the value you want to add to
 * @param val the value you want to add
 */
static inline void atomic_add(int *num, int val)
{
    asm volatile ("lock addl %1, %0"
                  : "+m" ((volatile int)*num)
                  : "ir" (val));
}

/**
 * @brief Atomic subtraction operation
 *
 * @param[out] num pointer to the value you want to subtract from
 * @param val the value you want to subtract
 */
static inline void atomic_subtract(int *num, int val)
{
    asm volatile ("lock subl %1, %0"
                  : "+m" ((volatile int)*num)
                  : "ir" (val));
}

/**
 * @brief Atomically adds 1 to a number, faster than a call to atomic_add(num,
 * 1)
 *
 * @param[out] num pointer to the value you want to add 1 to
 */
static inline void atomic_incrememt(int *num)
{
    asm volatile ("lock incl %0"
                  : "+m" ((volatile int)*num));
}

/**
 * @brief Atomically subtracts 1 from a number, faster than a call to
 * atomic_subtract(num, 1)
 *
 * @param[out] num pointer to the value you want to ubstract 1 from
 */
static inline void atomic_decrement(int *num)
{
    asm volatile ("lock decl %0"
                  : "+m" ((volatile int)*num));
}

/**
 * @brief Atomically exchange two values in memory, essentially an atomic set
 *
 * @param[out] num pointer to the value you want to set
 * @param val the value you want to set num to
 *
 * @return The atomically swapped value
 */
static inline int atomic_xchg(int *num, int val)
{
    int __val = val;

    asm volatile ("xchgl %0, %1"
                  : "=r" (__val), "+m" ((volatile int)*num)
                  : "0" (__val)
                  : "memory");

    return __val;
}

/**
 * @brief Atomically set a value and then check if the value that was set
 * remains (no other thread came in and changed it)
 *
 * @param[out] num pointer to the value you want to set
 * @param val the value you want to set
 *
 * @return 1 if the value was successfully set, 0 otherwise
 */
static inline int atomic_test_and_set(int *num, int val)
{
    int old_val;

    old_val = atomic_xchg(num, val);

    return old_val == val;
}

#endif /* _ATOMIC_OPS_H */
