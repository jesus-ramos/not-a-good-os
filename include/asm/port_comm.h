#ifndef _PORT_COMM_H
#define _PORT_COMM_H

#include <kernel/types.h>

void outportb(uint16_t port, uint8_t value);
uint8_t inportb(uint16_t port);
uint16_t inportw(uint16_t port);

#endif /* _PORT_COMM_H */
