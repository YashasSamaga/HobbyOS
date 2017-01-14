# Standard Library
# lib/makefile

# library make configuration
include lib/make.config

# library source files
LIB_CSOURCES = $(LIBDIR)/string.c $(LIBDIR)/stdlib.c
LIB_COBJECTS = $(BUILD_LIBDIR)/string.o $(BUILD_LIBDIR)/stdlib.o
LIB_OBJECTS = $(LIB_COBJECTS)

# define the compiler and archiver to use
CC = gcc
AR = ar

# define compiler and linker flags
CFLAGS = -Wall -Wextra -std=c99 -m32 -O -ffreestanding -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin 
ARFLAGS = rvs

# define directories containing header files
INCLUDES = -I./include

.PHONY: all clean
.SUFFIXES: .o .c

all: $(LIB_OBJECTS) archive

$(BUILD_LIBDIR)/%.o: $(LIBDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
		
archive:
	$(AR) $(ARFLAGS) $(LIBFILE) $(LIB_OBJECTS)
 
clean:
	rm *.o
