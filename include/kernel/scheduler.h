#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <kernel/task.h>

#define SCHED_TICK 50 /* 100 Hz */

void schedule();

extern volatile struct task *current;

#endif /* _SCHEDULER_H */
