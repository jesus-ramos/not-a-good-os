CC       = gcc
CFLAGS	 = -Wall -m32
LDFLAGS  = -nostdlib -fno-builtin -nostartfiles -nodefaultlibs
LD 	 = ld

AS	 = nasm
ASFLAGS  = -f elf

TARGET   = kernel.img
SRCS 	 = kernel.c screen.c
ASSRCS  = loader.s

OBJS	 = ${SRCS:.c=.o}
ASOBJS  = ${ASSRCS:.s=.o}

.SUFFIXES :
.SUFFIXES : .o .c .s

all : kernel.bin $(TARGET)

depend : .depend

.depend : $(SRCS)
	$(CC) $(CFLAGS) -MM $^

include .depend

$(TARGET) : FORCE
	dd if=/dev/zero of=pad bs=1 count=750
	cat stage1 stage2 pad kernel.bin > kernel.img

.s.o :
	$(AS) $(ASFLAGS) -o $@ $<

kernel.bin : $(OBJS) $(ASOBJS) linker.ld
	$(LD) -melf_i386 -T linker.ld -o kernel.bin $(OBJS) $(ASOBJS)

.c.o :
	$(CC) $(CFLAGS) $(LDFLAGS) -c $<

TAGS :
	find . -regex ".*\.[cChH]\(pp\)?" -print | etags -

.PHONY : clean FORCE mrproper
clean :
	-rm $(TARGET) $(OBJS) $(ASOBJS) kernel.bin

mrproper : clean
	-rm .depend pad