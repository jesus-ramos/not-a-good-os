#ifndef _PANIC_H
#define _PANIC_H

/**
 * @brief Macro for when the system enters an unrecoverable error. Logs the file
 * and line number of the error as well. This macro will lock up the system in
 * order to prevent further problems.
 *
 * @param[in] message message to print before panicking and locking up the
 * system
 */
#define PANIC(message) panic(message, __FILE__, __LINE__)

/**
 * @brief Macro for when a bug in the kernel is encountered. Logs the file and
 * line number of the bug. Should be used when a bug is found but is
 * recoverable.
 *
 * @param[in] message message to print information about the bug
 */
#define BUG(message) bug(message, __FILE__, __LINE__)

/**
 * @brief Macro that checks an error condition and reports a bug if the error
 * condition evaluates to true
 *
 * @param cond the bug condition
 * @param[in] message the message to log information about the bug
 */
#define BUG_ON(cond, message)                   \
    do {                                        \
        if (cond)                               \
            BUG(message);                       \
    } while (0)

void panic(const char *message, const char *file_name, unsigned int line_num);
void bug(const char *message, const char *file_name, unsigned int line_num);

#endif /* _PANIC_H */
