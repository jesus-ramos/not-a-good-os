#include <kernel/compiler.h>
#include <kernel/paging.h>
#include <kernel/scheduler.h>

#include <asm/common.h>
#include <asm/switch_to.h>

volatile struct task *current = NULL;

void schedule()
{
    unsigned long esp, ebp, eip;

    if (unlikely(!current))
        return;

    esp = read_esp();
    ebp = read_ebp();
    eip = read_eip();

    if (!eip)
        return;

    current->eip = eip;
    current->esp = esp;
    current->ebp = ebp;

    current_directory = current->page_directory;
    switch_task(eip, esp, ebp, current_directory->physical);
}
