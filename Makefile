CC	= gcc
CFLAGS	= -Wall -m32 -I./include/ -nostdlib -fno-builtin -nostartfiles \
	  -nodefaultlibs -mno-sse -O3 -g
AS	= nasm
ASFLAGS = -f elf -Ox

BINTYPE = elf_i386
LDCFG	= linker.ld
LDFLAGS = -m$(BINTYPE) -T ../$(LDCFG)
LD	= ld

TARGET	= kernel.bin
SYMS	= kernel.syms

BINDIR	= bin
DEPSDIR = deps
MKDIRS	= $(CURDIR)/{$(BINDIR),$(DEPSDIR)}

VPATH	= boot drivers kernel lib mem
# boot
SRCS	+= kernel.c
ASSRCS	+= loader.s
# drivers
SRCS	+= keyboard.c screen.c timer.c
# kernel
SRCS	+= console.c desc_tables.c isr.c panic.c printk.c
ASSRCS	+= gdt.s interrupt.s
# lib
SRCS	+= string.c vsprintf.c
# mem
SRCS	+= heap.c paging.c

OBJS	= ${SRCS:.c=.o}
ASOBJS	= ${ASSRCS:.s=.o}
DEPS	= ${SRCS:.c=.d}

.SUFFIXES :
.SUFFIXES : .o .c .s

$(shell `mkdir -p $(MKDIRS)`)

all : $(TARGET)

$(TARGET) : $(OBJS) $(ASOBJS) $(LDCFG)
	cd $(BINDIR);						\
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS) $(ASOBJS) &&	\
	objcopy --only-keep-debug $(TARGET) $(SYMS) &&		\
	objcopy --strip-debug $(TARGET);			\
	cd -

%.o : %.c
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ -c $<

%.o : %.s
	$(AS) $(ASFLAGS) -o $(BINDIR)/$@ $<

%.d : %.c
	@$(CC) -M $(CFLAGS) $< > $@.$$$$;				\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $(DEPSDIR)/$@;	\
	rm -f $@.$$$$

-include $(DEPS)

TAGS :
	find . -regex ".*\.[cChH]\(pp\)?" -print | etags -

clean :
	-rm -r $(BINDIR) $(DEPSDIR) 2>/dev/null || true

mrproper : clean
	-rm TAGS 2>/dev/null || true

.PHONY : clean mrproper TAGS
