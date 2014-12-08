/**
 * @file
 *
 * Functions for when the kernel encounters bugs and unrecoverable errors
 */

#include <asm/common.h>

#include <kernel/panic.h>
#include <kernel/stdio.h>

/**
 * @brief Function for when the kernel has entered an unrecoverable error, once
 * called the CPU that called it will halt to prevent further issues. Do not
 * call this directly, call PANIC() instead.
 *
 * @param[in] messsage message to print
 * @param[in] file_name the file name of where the error took place
 * @param line_num the line number where the error occured
 */
void panic(const char *message, const char *file_name, unsigned int line_num)
{
    disable_interrupts();

    printk("PANIC!! %s at %s : line %d.\n", message, file_name, line_num);

    seppuku(); /* Commit seppuku */
}

/**
 * @brief Function for when a bug is detected in the kernel that can be
 * recovered from, used for simple logging. Do not call this directly, call
 * BUG() or BUG_ON() instead.
 *
 * @param[in] messsage message to print
 * @param[in] file_name the file name of where the error took place
 * @param line_num the line number where the error occured
 */
void bug(const char *message, const char *file_name, unsigned int line_num)
{
    printk("BUG: %s at %s : line %d.\n", message, file_name, line_num);
}
