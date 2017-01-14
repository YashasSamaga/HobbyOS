# LindusOS Build script
# 'make'        build executable file 'KRNL.BIN'
# 'make clean'  removes all .o and executable files

# define the source and output files
# CSOURCES = $(shell find -maxdepth 2 -name '*.c')
# COBJECTS = $(patsubst %.c, %.o, $(CSOURCES))
# ASMSOURCES = $(shell find -maxdepth 2 -name '*.asm')
# ASMOBJECTS = $(patsubst %.asm, %.o, $(ASMSOURCES))

# Hardware Abstraction Layer Configuration (architecture specifications)
# The target architecture must be set in hal/make.config
include hal/make.config

#Kernel Configuration
include kernel/make.config

#Library Configuration
include lib/make.config

BUILDDIR = build
EXECUTABLE = $(BUILDDIR)/KRNL.BIN

LINKER = ld
LDFLAGS = -T link.ld -arch i386

OBJECTS = $(BUILD_HALDIR)/init.o $(BUILD_HALDIR)/hal.o $(BUILD_HALDIR)/textmode.o $(BUILD_HALDIR)/cpu/cpu.o $(BUILD_HALDIR)/cpu/gdt.o $(BUILD_HALDIR)/cpu/idt.o $(BUILD_HALDIR)/cpu/exceptions.o $(BUILD_HALDIR)/irq.o $(BUILD_HALDIR)/swints.o $(BUILD_HALDIR)/chips/pic-i8259.o $(BUILD_HALDIR)/chips/pit-i8253.o $(BUILD_HALDIR)/memory/phys_mm.o $(LIBFILE) $(KERNELFILE)
# 

all: build_hal build_lib build_kernel link
build_hal:
	make -f hal/x86/makefile
	
build_lib:
	make -f lib/makefile

build_kernel:
	make -f kernel/makefile
	
link:
	$(LINKER) $(LDFLAGS) -o $(EXECUTABLE) $(OBJECTS)
	
clean:
#del lib\*.o
#del lib\*.a
	
	del hal\x86\*.o
	del hal\x86\cpu\*.o
	del hal\*.a
	
#del kernel\*.o
#del kernel\*.a
	
	del build\KRNL.bin
