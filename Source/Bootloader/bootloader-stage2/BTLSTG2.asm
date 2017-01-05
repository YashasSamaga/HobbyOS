;*****************************************************************************
; Bootloader (second stage)
;
; BTLSTG2.asm
;*****************************************************************************
bits	16
org 0x500

jmp	main

;*****************************************************************************
; Includes
;*****************************************************************************
%include "gdt.asm"			; Gdt routines
%include "A20.asm"			; A20 enabling
%include "Fat12.asm"			; FAT12 driver. Kinda :)

;*****************************************************************************
; Data Declarations
;*****************************************************************************
%define IMAGE_PMODE_BASE 0x100000 ; protected mode location
%define IMAGE_RMODE_BASE 0x3000 ; real mode location (temporary)

;*****************************************************************************
; Data Declarations
;*****************************************************************************
ImageSize     db 0
ImageName     db "KRNL    BIN"

msgLoadFailure 			DB 0x0D, "KRNL.BIN is missing or corrupt.", 0x0A, 0x00
msgAwaitKeypress 		DB 0x0D, "Press any key to restart.", 0x0A, 0x00

;*****************************************************************************
; puts
; Prints a string using BIOS interrupt 0x10
;
; DS:SI => address of the null-terminated string
;*****************************************************************************
puts:
	lodsb
	or		al, al
	jz		.putsDone
	mov		ah, 0x0E	; print character function
	int		0x10
	jmp		puts
.putsDone:
	ret

;*****************************************************************************
; awaitKeypressAndReboot
; Sends await keypress message and waits for a keypress after which it reboots
;*****************************************************************************
awaitKeypressAndReboot:
	mov si, msgAwaitKeypress
	call puts
		
	mov ah, 0x01
	mov ch, 00010000b
	int 0x10
		
	; await keypress
    mov     ah, 0x00
    int     0x16			
		
	; cold reboot
	xor ax, ax
	mov WORD [0x00472], ax
	jmp 0xFFFF:0x00   

;*****************************************************************************
; Stage 2 Entry
;*****************************************************************************
main:
	;set the segment registers
	cli
	xor	ax, ax
	mov	ds, ax
	mov	es, ax
	
	; create the stack
	mov	ax, 0x0
	mov	ss, ax
	mov	sp, 0x7C00 ; use the space below the bootsector
	sti
	
	call LoadRoot

	mov	ebx, 0
    mov	bp, IMAGE_RMODE_BASE
	mov	si, ImageName
	call	LoadFile
	
	mov	DWORD [ImageSize], ecx
	cmp	ax, 0
	je	EnterStage3
	
	mov		si, msgLoadFailure
	call	puts
	call 	awaitKeypressAndReboot
	cli
	hlt

EnterStage3:
	call InstallGDT
	call EnableA20
	
	cli
	mov	eax, cr0
	or	eax, 1
	mov	cr0, eax

	jmp	CODE_DESC:Stage3

;******************************************************
;	ENTRY POINT FOR STAGE 3
;******************************************************
bits 32

Stage3:
	mov	ax, DATA_DESC	; set data segments to data selector (0x10)
	mov	ds, ax
	mov	ss, ax
	mov	es, ax
	mov	esp, 90000h		; stack begins from 90000h

  	mov	eax, dword [ImageSize]
  	movzx	ebx, word [bpbBytesPerSector]
  	mul	ebx
  	mov	ebx, 4
  	div	ebx
   	cld
   	mov    esi, IMAGE_RMODE_BASE
   	mov	edi, IMAGE_PMODE_BASE
   	mov	ecx, eax
   	rep	movsd

	jmp	CODE_DESC:IMAGE_PMODE_BASE

	cli
	hlt

