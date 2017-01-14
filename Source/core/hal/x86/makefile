# x86 Hardware Abstraction Layer
# hal/x86/makefile

# HAL Make Configuration
include hal/make.config

# HAL source files
#HAL_CSOURCES = $(wildcard cpu/*.c) $(wildcard *.c) $(wildcard chips/*.c)
#HAL_COBJECTS = $(patsubst %.c, %.o, $(HAL_CSOURCES))

HAL_CSOURCES = $(HALDIR)/hal.c $(HALDIR)/textmode.c $(HALDIR)/cpu/cpu.c $(HALDIR)/cpu/gdt.c $(HALDIR)/cpu/idt.c $(HALDIR)/cpu/exceptions.c $(HALDIR)/irq.c $(HALDIR)/chips/pic-i8259.c $(HALDIR)/chips/pit-i8253.c $(HALDIR)/swints.c 
HAL_COBJECTS = $(BUILD_HALDIR)/hal.o $(BUILD_HALDIR)/textmode.o $(BUILD_HALDIR)/cpu/cpu.o $(BUILD_HALDIR)/cpu/gdt.o $(BUILD_HALDIR)/cpu/idt.o $(BUILD_HALDIR)/cpu/exceptions.o $(BUILD_HALDIR)/irq.o $(BUILD_HALDIR)/chips/pic-i8259.o $(BUILD_HALDIR)/chips/pit-i8253.o $(BUILD_HALDIR)/swints.o 
HAL_ASMSOURCES = $(HALDIR)/init.asm
HAL_ASMOBJECTS = $(BUILD_HALDIR)/init.o
HAL_OBJECTS = $(HAL_ASMOBJECTS) $(HAL_COBJECTS)

# define the compiler, assembler and archiver to use
CC = gcc
ASMA = nasm
AR = ar

# define directories containing header files
INCLUDES = -I$(realpath $(HALDIR)/include) -I$(realpath include)

# define compiler, assembler and linker flags
CFLAGS =  -Wall -Wextra -O -ffreestanding -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin
ASMFLAGS = -f aout
ARFLAGS = rvs

.PHONY: all clean

all: $(HAL_OBJECTS) archive

$(BUILD_HALDIR)/%.o: $(HALDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_HALDIR)/%.o: $(HALDIR)/%.asm 
	$(ASMA) $(ASMFLAGS) -o $@ $<

archive:
	$(AR) $(ARFLAGS) $(HALFILE) $(HAL_OBJECTS)
 
clean:
#TODO
