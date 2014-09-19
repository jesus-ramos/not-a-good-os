#include <kernel/heap.h>
#include <kernel/paging.h>
#include <kernel/scheduler.h>
#include <kernel/task.h>

#include <asm/common.h>

pid_t next_pid = 0;

pid_t fork()
{
    struct task *parent;
    struct page_directory *page_dir;
    struct task *new_task;
    unsigned long eip;

    disable_interrupts();

    parent = (struct task *)current; /* Cast required because volatile */
    page_dir = clone_directory(current_directory);

    new_task = kmalloc(sizeof(struct task));
    new_task->pid = next_pid++;
    new_task->esp = 0;
    new_task->ebp = 0;
    new_task->eip = 0;
    new_task->page_directory = page_dir;

    /* This function will fork a new process at this point */
    eip = read_eip();

    if (current == parent)
    {
        new_task->esp = read_esp();
        new_task->ebp = read_ebp();
        new_task->eip = eip;
        enable_interrupts();
        return new_task->pid;
    }

    return 0;
}
