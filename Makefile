CC      = gcc
CFLAGS	= -Wall -m32 -I./include/ -nostdlib -fno-builtin -nostartfiles \
	  -nodefaultlibs -mno-sse -O3 -g

AS	= nasm
ASFLAGS = -f elf -Ox

BINTYPE = elf_i386
LDCFG	= linker.ld
LDFLAGS = -m$(BINTYPE) -T $(LDCFG)
LD 	= ld

TARGET  = kernel.bin
SYMS	= kernel.syms

SRCS 	= kernel.c screen.c string.c desc_tables.c isr.c timer.c 	\
	  vsprintf.c printk.c keyboard.c paging.c panic.c console.c 	\
	  heap.c
VPATH 	= boot drivers init kernel lib mem

ASSRCS  = loader.s gdt.s interrupt.s
OBJS	= ${SRCS:.c=.o}
ASOBJS  = ${ASSRCS:.s=.o}
DEPS 	= ${SRCS:.c=.d}

.SUFFIXES :
.SUFFIXES : .o .c .s

all : $(TARGET)

$(TARGET) : $(OBJS) $(ASOBJS) $(LDCFG)
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

%.d : %.c
	@$(CC) -M $(CFLAGS) $< > $@.$$$$;			\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; 	\
	rm -f $@.$$$$

-include $(DEPS)

TAGS :
	@echo "GEN: TAGS"
	@find . -regex ".*\.[cChH]\(pp\)?" -print | etags -

clean :
	@echo "CLEAN"
	-@rm $(TARGET) $(OBJS) $(ASOBJS) $(SYMS) $(DEPS) 2>/dev/null || true

mrproper : clean
	@echo "MRPROPER"
	-@rm TAGS 2>/dev/null || true

.PHONY : clean mrproper TAGS
