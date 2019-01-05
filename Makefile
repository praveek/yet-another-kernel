
AS = /Users/praveeku/exp/tmp/output/bin/i686-elf-as
CC = /Users/praveeku/exp/tmp/output/bin/i686-elf-gcc
CXX = /Users/praveeku/exp/tmp/output/bin/i686-elf-g++


C_SOURCES = 
CPP_SOURCES = kernel/kernel.cpp \
	kernel/arch/x86/arch.cpp \
	kernel/arch/x86/gdt.cpp \
	kernel/arch/x86/idt.cpp
ASM_SOURCES = kernel/arch/x86/boot.s \
	kernel/arch/x86/descriptor.s

CRTI_OBJ = kernel/arch/x86/stdlib/crti.o
CRTN_OBJ = kernel/arch/x86/stdlib/crtn.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)

OBJS = ${CPP_SOURCES:.cpp=.o} ${C_SOURCES:.c=.o} ${ASM_SOURCES:.s=.o}
INTERNAL_OBJS:=$(CRTI_OBJ) $(OBJS) ${CRTN_OBJ}
OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)

# $(info $$OBJS is [${OBJ_LINK_LIST}])

all: kernel

%.o: %.cpp
	${CXX} -c $< -o $@ -std=c11 -ffreestanding -O2 -Wall -Wextra

%.o: %.c
	${CC} -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

%.o: %.s
	${AS} $< -o $@

kernel: ${INTERNAL_OBJS}
	${CC} -T kernel/arch/x86/linker.ld ${OBJ_LINK_LIST} -o kernel.bin -ffreestanding -O2 -nostdlib -lgcc

run: kernel
	qemu-system-i386 -kernel kernel.bin

clean:
	rm -rf ${INTERNAL_OBJS} kernel.bin  