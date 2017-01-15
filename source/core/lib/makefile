# Standard Library
# lib/makefile

# HAL make configuration
include hal/make.config

# library make configuration
include lib/make.config

# library source and object files
LIB_CSOURCES = $(wildcard $(LIBDIR)/*.c)
LIB_COBJECTS = $(addprefix $(BUILDDIR)/, $(patsubst %.c, %.o, $(LIB_CSOURCES)))

LIB_OBJECTS = $(LIB_COBJECTS)

# define the compiler and archiver to use
CC = gcc
AR = ar

# -Wall -Wextra -Werror => Enable all warnings and consider warnings as errors
# -O1,O2,O3 => O3 highest optimization level (we target for O3)
# -Og => generate debug code
# -fno-asm => asm, inline, typeof keywords are NOT recognized; however, __asm__, __inline__ and __typeof__ are recognized
# -ffreestanding => implies -fno-builtin; assumes the target is being built for a non hosted environment; __builtin_ functions are still usable
# -nostdinc, -nostdlib => tell GCC not to use default libraries and includes
CFLAGS = -Wall -Wextra -Werror -std=c99 -fno-asm -ffreestanding -nostdinc -nostdlib -O3 $(HALARCH_CFLAG)
ARFLAGS = rvs

# define directories containing header files
INCLUDES = -I./include

.PHONY: all archive clean

all: $(LIB_OBJECTS) archive

$(BUILD_LIBDIR)/%.o: $(LIBDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
		
archive:
	$(AR) $(ARFLAGS) $(LIBFILE) $(LIB_OBJECTS)
 
clean:
	rm $(LIB_OBJECTS)