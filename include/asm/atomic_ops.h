#ifndef _ATOMIC_OPS_H
#define _ATOMIC_OPS_H

static inline void atomic_add(int *num, int val)
{
    asm volatile ("lock addl %1, %0"
                  : "+m" ((volatile int)*num)
                  : "ir" (val));
}

static inline void atomic_subtract(int *num, int val)
{
    asm volatile ("lock subl %1, %0"
                  : "+m" ((volatile int)*num)
                  : "ir" (val));
}

static inline void atomic_incrememt(int *num)
{
    asm volatile ("lock incl %0"
                  : "+m" ((volatile int)*num));
}

static inline void atomic_decrement(int *num)
{
    asm volatile ("lock decl %0"
                  : "+m" ((volatile int)*num));
}

static inline int atomic_xchg(int *num, int val)
{
    int __val = val;
    
    asm volatile ("xchgl %0, %1"
                  : "=r" (__val), "+m" ((volatile int)*num)
                  : "0" (__val)
                  : "memory");

    return __val;
}

static inline int atomic_test_and_set(int *num, int val)
{
    int old_val;

    old_val = atomic_xchg(num, val);

    return old_val == val;
}

#endif /* _ATOMIC_OPS_H */
