# LindusOS Build script
# 'make'        build executable file 'KRNL.BIN'
# 'make clean'  removes all .o and executable files

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
LDFLAGS = -T link.ld -m elf_i386 $(HAL_LDFLAGS)

OBJECTS = $(BUILD_HALDIR)/init.o $(BUILD_HALDIR)/hal.o $(BUILD_HALDIR)/textmode.o $(BUILD_HALDIR)/cpu/cpu.o $(BUILD_HALDIR)/cpu/gdt.o $(BUILD_HALDIR)/cpu/idt.o $(BUILD_HALDIR)/cpu/exceptions.o $(BUILD_HALDIR)/irq.o $(BUILD_HALDIR)/swints.o $(BUILD_HALDIR)/chips/pic-i8259.o $(BUILD_HALDIR)/chips/pit-i8253.o $(BUILD_HALDIR)/memory/phys_mm.o $(LIBFILE) $(KERNELFILE)

.PHONY: all build_hal build_lib build_kernel clean_hal clean_lib clean_kernel clean_all link

all: build_hal build_lib build_kernel link
build_hal:
	make -f hal/x86/makefile
	
build_lib:
	make -f lib/makefile

build_kernel:
	make -f kernel/makefile

link:
	$(LINKER) $(LDFLAGS) -o $(EXECUTABLE) $(OBJECTS)
	
clean_hal:
	make -f hal/x86/makefile clean
	
clean_lib:
	make -f lib/makefile clean

clean_kernel:
	make -f kernel/makefile clean

clean_all: clean_hal clean_lib clean_kernel	
	
