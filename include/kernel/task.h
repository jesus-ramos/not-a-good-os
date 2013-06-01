#ifndef _TASK_H
#define _TASK_H

#include <kernel/types.h>

/**
 * @brief Structure for an executable task
 */
struct task
{
    pid_t pid; /**< Process ID of the task */
    unsigned int esp; /**< Stack pointer for the task */
    unsigned int ebp; /**< Base pointer for the task */
    unsigned int eip; /**< Instruction pointer for the task */
    struct page_directory *page_directory; /**< Page table page directory of */
                                           /**< the task */
};

void init_tasking();
pid_t fork();
void move_stack(void *new_stack_ptr, unsigned int size);
int get_current_pid();

#endif /* _TASK_H */
