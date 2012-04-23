CC       = gcc
CFLAGS	 = -Wall -m32 -I./include/ -nostdlib -fno-builtin -nostartfiles -nodefaultlibs
LDFLAGS  = -melf_i386 -T linker.ld
LD 	 = ld
AS	 = nasm
ASFLAGS  = -f elf

TARGET   = kernel.bin
SRCS 	 = kernel.c screen.c string.c desc_tables.c isr.c
ASSRCS   = loader.s gdt.s interrupt.s

OBJS	 = ${SRCS:.c=.o}
ASOBJS   = ${ASSRCS:.s=.o}

.SUFFIXES :
.SUFFIXES : .o .c .s

all : $(TARGET)

depend : .depend

.depend : $(SRCS)
	$(CC) $(CFLAGS) -MM $^ > .depend

include .depend

.s.o :
	$(AS) $(ASFLAGS) -o $@ $<

$(TARGET) : $(OBJS) $(ASOBJS) linker.ld
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS) $(ASOBJS)

.c.o :
	$(CC) $(CFLAGS) -c $<

TAGS :
	find . -regex ".*\.[cChH]\(pp\)?" -print | etags -

.PHONY : clean FORCE mrproper
clean :
	-rm $(TARGET) $(OBJS) $(ASOBJS)

mrproper : clean
	-rm .depend