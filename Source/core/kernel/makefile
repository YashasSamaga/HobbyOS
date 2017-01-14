# Kernel
# kernel/makefile

# kernel make configuration
include kernel/make.config

# kernel source files
KERNEL_CSOURCES = $(KERNELDIR)/main.c 
KERNEL_COBJECTS = $(BUILD_KERNELDIR)/main.o 
KERNEL_OBJECTS = $(KERNEL_COBJECTS)

# define the compiler and linker to use
CC = gcc
AR = ar

# define compiler and linker flags
CFLAGS = -Wall -Wextra -std=c99 -m32 -O -ffreestanding -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin
ARFLAGS = rvs

# define directories containing header files
INCLUDES = -I./include

.PHONY: all clean

all: $(KERNEL_OBJECTS) link

$(BUILD_KERNELDIR)/%.o: $(KERNELDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
		
link:
	$(AR) $(ARFLAGS) $(KERNELFILE) $(KERNEL_OBJECTS)
 
clean:
#TODO
