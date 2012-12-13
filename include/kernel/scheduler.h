#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include <kernel/task.h>

void schedule();

extern volatile struct task *current;

#endif /* _SCHEDULER_H */
