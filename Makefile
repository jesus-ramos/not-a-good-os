CC      = gcc
CFLAGS	= -Wall -m32 -I./include/ -nostdlib -fno-builtin -nostartfiles \
	  -nodefaultlibs -mno-sse -O3 -g
LDFLAGS = -melf_i386 -T linker.ld
LD 	= ld
AS	= nasm
ASFLAGS = -f elf -Ox

TARGET  = kernel.bin
SYMS	= kernel.syms
SRCS 	= kernel.c screen.c string.c desc_tables.c isr.c timer.c \
	  vsprintf.c printk.c keyboard.c paging.c panic.c console.c
ASSRCS  = loader.s gdt.s interrupt.s
OBJS	= ${SRCS:.c=.o}
ASOBJS  = ${ASSRCS:.s=.o}

.SUFFIXES :
.SUFFIXES : .o .c .s

all : $(TARGET)

depend : .depend

.depend : $(SRCS)
	$(CC) $(CFLAGS) -MM $^ > .depend

include .depend

$(TARGET) : $(OBJS) $(ASOBJS) linker.ld
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS) $(ASOBJS)
	objcopy --only-keep-debug $(TARGET) $(SYMS)
	objcopy --strip-debug $(TARGET)

.c.o :
	$(CC) $(CFLAGS) -c $<

.s.o :
	$(AS) $(ASFLAGS) -o $@ $<

TAGS : FORCE
	find . -regex ".*\.[cChH]\(pp\)?" -print | etags -

.PHONY : clean FORCE mrproper
clean :
	-rm $(TARGET) $(OBJS) $(ASOBJS) $(SYMS)

mrproper : clean
	-rm .depend TAGS