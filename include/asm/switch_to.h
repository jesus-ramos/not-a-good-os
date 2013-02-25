#ifndef _SWITCH_TO_H
#define _SWITCH_TO_H

/**
 * @brief Switches the currently executing task for a new one
 *
 * @param new_eip new instruction pointer for the task to execute
 * @param new_esp new stack pointer for the task to execute
 * @param new_ebp new base pointer for the task to execute
 * @param page_dir_addr the address of the page directory for the task to
 * execute
 */
static inline void switch_task(unsigned long new_eip, unsigned long new_esp,
                               unsigned long new_ebp,
                               unsigned long page_dir_addr)
{
    asm volatile ("cli\n\t"
                  "mov %0, %%ecx\n\t"
                  "mov %1, %%esp\n\t"
                  "mov %2, %%ebp\n\t"
                  "mov %3, %%cr3\n\t"
                  "mov $0, %%eax\n\t"
                  "sti\n\t"
                  "jmp *%%ecx"
                  : : "r" (new_eip), "r" (new_esp), "r" (new_ebp),
                    "r" (page_dir_addr));
}

#endif /* _SWITCH_TO_H */
