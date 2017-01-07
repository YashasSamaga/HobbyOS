;******************************************************************************
;	Hardware Abstraction Layer x86
;
;	HAL Entry Stub
;	The bootloader will call start which initiates the HAL initilization process.
;
;	stub_entry.c
;	Date: January 6th 2017
;
;******************************************************************************
bits 32

;******************************************************************************
; 	Entry Function
;******************************************************************************
global start ; must be visible to the linker

start:
	cli
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov	esp, 0x7FFFF
	jmp 0x08:start2
	
start2:
	extern _hal_initialize
	jmp _hal_initialize
	cli
	hlt
	
global _default_handler
_default_handler:
 cli
    push byte 0
    push byte 0
    jmp isr_common_stub
	
extern _fault_handler

isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, _fault_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret