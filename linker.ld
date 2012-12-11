ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
    . = 0x00100000;

    /* If $(BINDIR) changes, change it here as well */
    .MBHEADER :
    AT (0x00100000)
    {
        bin/loader.o
    }

    .text ALIGN (0x1000) :
    {
        *(.text)
        *(.rodata*)
    }

    .rodata ALIGN (0x1000) :
    {
        *(.rodata*)
    }

    .data ALIGN (0x1000) :
    {
        *(.data)
    }

    .bss :
    {
        sbss = .;
        *(COMMON)
        *(.bss)
        ebss = .;
    }

    end = .; _end = .; __end = .;
}
