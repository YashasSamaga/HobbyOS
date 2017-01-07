# Kernel
# kernel/makefile

# kernel make configuration
include kernel/make.config

# kernel source files
KERNEL_CSOURCES = kernel/main.c 
KERNEL_COBJECTS = kernel/main.o 
KERNEL_OBJECTS = $(KERNEL_COBJECTS)

# define the compiler and linker to use
CC = gcc
AR = ar

# define compiler and linker flags
CFLAGS = -Wall -O -ffreestanding -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin
ARFLAGS = rvs

# define directories containing header files
INCLUDES = -I./include

.PHONY: all clean
.SUFFIXES: .o .c

all: $(KERNEL_OBJECTS) link

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
		
link:
	$(AR) $(ARFLAGS) $(KERNELFILE) $(KERNEL_OBJECTS)
 
clean:
	rm kernel/*.o