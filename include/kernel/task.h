#ifndef _TASK_H
#define _TASK_H

#include <kernel/types.h>

struct task
{
    pid_t pid;
    unsigned int esp;
    unsigned int ebp;
    unsigned int eip;
    struct page_directory *page_directory;
};

void init_tasking();
pid_t fork();
void move_stack(void *new_stack_ptr, unsigned int size);
int get_current_pid();

#endif /* _TASK_H */
