ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
    . = 0x00100000;

    .MBHEADER : AT (0x00100000) { loader.o }

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
}