# Standard Library
# lib/makefile

# library make configuration
include lib/make.config

# library source files
LIB_CSOURCES = lib/string.c lib/stdlib.c
LIB_COBJECTS = lib/string.o lib/stdlib.o
LIB_OBJECTS = $(LIB_COBJECTS)

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

all: $(LIB_OBJECTS) archive

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
		
archive:
	$(AR) $(ARFLAGS) $(LIBFILE) $(LIB_OBJECTS)
 
clean:
	rm *.o