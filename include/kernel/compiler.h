#ifndef _COMPILER_H
#define _COMPILER_H

#ifndef likely
#define likely(x) __builtin_expect(!!(x), 1)
#endif /* likely */

#ifndef unlikely
#define unlikely(x) __builtin_expect(!!(x), 0)
#endif /* unlikely */

/* Use intrinsics if possible */
#ifndef barrier
#define barrier() __memory_barrier()
#endif /* barrier */

#ifndef barrier
#define barrier() asm volatile ("" : : : "memory")
#endif /* barrier */

#define unreachable() do { } while (1)

#endif /* _COMPILER_H */
