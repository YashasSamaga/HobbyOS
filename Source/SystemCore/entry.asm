;********************************************************************************
;Lindus Kernel Entry Script
;Author   : Yashas Samaga
;Date     : 21-04-2012
;Description: This script is the entry point of the kenrel.This script will just 
;              setup the stack and jump to C function "init_system".
;
;Copyright (C) Yashas Samaga <yashas_2010@yahoo.com>
;********************************************************************************
BITS 32
extern _init_system
global start

start:
;mov esp, _kernel_stack
call _init_system
cli
hlt

ALIGN 4
mboot:
    MULTIBOOT_PAGE_ALIGN	equ 1<<0
    MULTIBOOT_MEMORY_INFO	equ 1<<1
    MULTIBOOT_AOUT_KLUDGE	equ 1<<16
    MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
    MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
    EXTERN code, bss, end

    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM

    dd mboot
    dd code
    dd bss
    dd end
    dd start


