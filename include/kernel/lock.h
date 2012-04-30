#ifndef _LOCK_H
#define _LOCK_H

#include <asm/atomic_ops.h>

#define LOCKED   1
#define UNLOCKED 0

typedef int spinlock_t;

static inline void spin_lock(spinlock_t *lock)
{
    while (atomic_test_and_set(lock, LOCKED));
}

static inline void spin_unlock(spinlock_t *lock)
{
    atomic_xchg(lock, UNLOCKED);
}

static inline void init_spinlock(spinlock_t *lock)
{
    *lock = UNLOCKED;
}

#endif /* _LOCK_H */
