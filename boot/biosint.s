    .code16gcc                  ; we're in protected mode, run in 16 bit
    .text
    .globl  bios_call_interrupt
    .type   bios_call_interrupt, @function

bios_call_interrupt:
    /* Do something really nasty, modify the int instruction */
    cmp     %al, 3f
    je      1f
    movb    %al, 3f
    jmp     1f

1:
    /* Save the general purpose segment registers */
    pushfl
    pushw   %fs
    pushw   %gs
    pushal

    /* Copy the input to the stack */
    subw    $44, %sp
    movw    %dx, %si
    movw    %sp, %di
    movw    $11, %cx
    rep

    /* Pop the state from the stack */
    popal
    popw    %gs
    popw    %fs
    popw    %es
    popw    %ds
    popfl

    /* Modify the int instruction, because we can and it works */
    .byte   0xCD
3:  .byte   0

    /* Push state to the stack, same as pop but backwards :) */
    pushfl
    pushw   %ds
    pushw   %es
    pushw   %fs
    pushw   %gs
    pushal

    /* Play nice with C */
    cld
    movzwl  %sp, %esp
    movw    %cs, %ax
    movw    %ax, %ds
    movw    %ax, %es

    /* Get the output state */
    movw    68(%esp), %di
    andw    %di, %di
    jz      4f
    movw    %sp, %si
    movw    $11, %cx
    rep
4:  addw    $44, %sp

    /* Restore old values and get out of here */
    popal
    popw    %gs
    popw    %fs
    popfl
    retl
    .size   bios_call_interrupt, .-bios_call_interrupt
