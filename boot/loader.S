#define ASM_FILE 1
#include "multiboot.h"

#define STACK_SIZE 0x4000 /* 16k stack size */

#define MULTIBOOT_HEADER_FLAGS 0x3 /* We're an ELF binary */

        .text
        .globl  loader, _loader
loader:
_loader:
        jmp     multiboot_entry

        .align 4

multiboot_header:
        .long   MULTIBOOT_HEADER_MAGIC
        .long   MULTIBOOT_HEADER_FLAGS
        .long   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

multiboot_entry:
        movl    $(stack + STACK_SIZE), %esp
        pushl   $0
        popf
        pushl   %eax    /* Magic value */
        pushl   %ebx    /* Pointer to struct multiboot_info */
        call    kmain

        .globl  hang
hang:
        hlt
        jmp     hang

        .comm   stack, STACK_SIZE
