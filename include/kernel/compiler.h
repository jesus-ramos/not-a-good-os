#ifndef _COMPILER_H
#define _COMPILER_H

/**
 * @def likely(x)
 *
 * @brief Give a compiler hint that this branch is very likely to happen
 *
 * @param x boolean expression for likely branch
 */
#ifndef likely
#define likely(x) __builtin_expect(!!(x), 1)
#endif /* likely */

/**
 * @def unlikely(x)
 *
 * @brief Give a compiler hint that this branch is unlikely to happen. Useful
 * for uncommon errors.
 *
 * @param x boolean expression which is unlikely to be true
 */
#ifndef unlikely
#define unlikely(x) __builtin_expect(!!(x), 0)
#endif /* unlikely */

/**
 * @def barrier()
 *
 * @brief Memory barrier operation, makes sure that all pending memory
 * operations are flushed once we proceed past this fence
 */
/* Use intrinsics if possible */
#ifndef barrier
#define barrier() __memory_barrier()
#endif /* barrier */

#ifndef barrier
#define barrier() asm volatile ("" : : : "memory")
#endif /* barrier */

/**
 * @brief Useful macro for eliminating warnings for unreachable code
 */
#define unreachable() do { } while (1)

#endif /* _COMPILER_H */
