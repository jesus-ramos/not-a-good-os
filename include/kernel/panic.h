#ifndef _PANIC_H
#define _PANIC_H

#define PANIC(message) panic(message, __FILE__, __LINE__)
#define BUG(message) bug(message, __FILE__, __LINE__)

void panic(const char *message, const char *file_name, unsigned int line_num);
void bug(const char *message, const char *file_name, unsigned int line_num);

#endif /* _PANIC_H */
