# x86 Hardware Abstraction Layer
# hal/x86/makefile

# HAL Make Configuration
include hal/make.config

# HAL source files
HAL_CSOURCES = $(HALDIR)/hal.c $(HALDIR)/textmode.c $(HALDIR)/cpu/cpu.c $(HALDIR)/cpu/gdt.c $(HALDIR)/cpu/idt.c 
HAL_COBJECTS = $(HALDIR)/hal.o $(HALDIR)/textmode.o $(HALDIR)/cpu/cpu.o $(HALDIR)/cpu/gdt.o $(HALDIR)/cpu/idt.o 
HAL_ASMSOURCES = $(HALDIR)/init.asm
HAL_ASMOBJECTS = $(HALDIR)/init.o
HAL_OBJECTS = $(HAL_ASMOBJECTS) $(HAL_COBJECTS)

# define the compiler, assembler and archiver to use
CC = gcc
ASMA = nasm
AR = ar

# define compiler, assembler and linker flags
CFLAGS = -Wall -O -ffreestanding -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin
ASMFLAGS = -f aout
ARFLAGS = rvs

# define directories containing header files
INCLUDES = -I./include

.PHONY: all clean
.SUFFIXES: .o .c .asm

all: $(HAL_OBJECTS) archive

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

.asm.o:
	$(ASMA) $(ASMFLAGS) -o $@ $<
		
archive:
	$(AR) $(ARFLAGS) $(HALFILE) $(HAL_OBJECTS)
 
clean:
	rm hal/hal.o
	rm $(HALDIR)/*.o