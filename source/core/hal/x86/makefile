# x86 Hardware Abstraction Layer
# hal/x86/makefile

# HAL Make Configuration
include hal/make.config

# HAL source and object files
HAL_CSOURCES = $(wildcard $(HALDIR)/*.c $(HALDIR)/cpu/*.c $(HALDIR)/memory/*.c $(HALDIR)/chips/*.c)
HAL_COBJECTS = $(addprefix $(BUILDDIR)/, $(patsubst %.c, %.o, $(HAL_CSOURCES)))

HAL_ASMSOURCES = $(wildcard $(HALDIR)/*.asm)
HAL_ASMOBJECTS = $(addprefix $(BUILDDIR)/, $(patsubst %.asm, %.o, $(HAL_ASMSOURCES)))

HAL_OBJECTS = $(HAL_ASMOBJECTS) $(HAL_COBJECTS)

# define the compiler, assembler and archiver to use
CC = gcc
ASMA = nasm
AR = /opt/cross/i386-aout/bin/ar

# -Wall -Wextra -Werror => Enable all warnings and consider warnings as errors
# -O1,O2,O3 => O3 highest optimization level (we target for O3)
# -Og => generate debug code
# -fno-asm => asm, inline, typeof keywords are NOT recognized; however, __asm__, __inline__ and __typeof__ are recognized
# -ffreestanding => implies -fno-builtin; assumes the target is being built for a non hosted environment; __builtin_ functions are still usable
# -nostdinc, -nostdlib => tell GCC not to use default libraries and includes
CFLAGS = -Wall -Wextra -std=c99 -fno-asm -ffreestanding -nostdinc -nostdlib -O1 $(HALARCH_CFLAG)
ASMFLAGS = -f $(HALARCH_ASMFLAG)
ARFLAGS = rvs

# define directories containing header files
INCLUDES = -I./$(HALDIR)/include -I./include

.PHONY: all archive clean

all: $(HAL_OBJECTS) archive

$(BUILD_HALDIR)/%.o: $(HALDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(BUILD_HALDIR)/%.o: $(HALDIR)/%.asm 
	$(ASMA) $(ASMFLAGS) -o $@ $<

archive:
	$(AR) $(ARFLAGS) $(HALFILE) $(HAL_OBJECTS)
 
clean:
	rm $(HAL_OBJECTS)
