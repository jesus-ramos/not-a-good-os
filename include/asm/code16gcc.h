/**
 * @file
 *
 * XXX: This file should not be included directly.
 *
 * Because GCC doesn't support an -m16 option we have to include this file
 * before anything else to ensure we are building the correct binary.
 *
 * Required for the early initialization code in Real Mode before the switch to
 * Protected Mode as we need to emit 32 bit code that will run in a 16 bit
 * segment space.
 */
#ifndef _ASM_CODE16GCC_H
#define _ASM_CODE16GCC_H

asm (".code16gcc");

#endif /* _ASM_CODE16GCC_H */
