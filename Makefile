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

.depend : $(SRCS)
	@echo "DEPEND"
	@$(CC) $(CFLAGS) -MM $^ > .depend

include .depend

$(TARGET) : $(OBJS) $(ASOBJS) linker.ld
	@echo "LD: $(TARGET)"
	@$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS) $(ASOBJS)
	@echo "OBJCOPY: $(SYMS)"
	@objcopy --only-keep-debug $(TARGET) $(SYMS)
	@echo "OBJCOPY: $(TARGET)"
	@objcopy --strip-debug $(TARGET)

.c.o :
	@echo "CC: $<"
	@$(CC) $(CFLAGS) -c $<

.s.o :
	@echo "AS: $<"
	@$(AS) $(ASFLAGS) -o $@ $<

TAGS :
	@echo "GEN: TAGS"
	@find . -regex ".*\.[cChH]\(pp\)?" -print | etags -

clean :
	@echo "CLEAN"
	-@rm $(TARGET) $(OBJS) $(ASOBJS) $(SYMS) 2>/dev/null || true

mrproper : clean
	@echo "MRPROPER"
	-@rm .depend TAGS 2>/dev/null || true

.PHONY : clean mrproper TAGS
