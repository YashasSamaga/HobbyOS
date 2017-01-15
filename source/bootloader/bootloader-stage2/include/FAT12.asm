;*****************************************************************************
; Bootloader (second stage)
; Real Mode Floppy Interface BIOS Routines
;	
; floppy16.asm
;*****************************************************************************
bits	16

;*****************************************************************************
; Includes
;*****************************************************************************
%include "Floppy16.asm"

;*****************************************************************************
; Defines
;*****************************************************************************
%define ROOT_OFFSET 0x2e00
%define FAT_SEG 0x2c0
%define ROOT_SEG 0x2e0

;*****************************************************************************
; Data Declarations
;*****************************************************************************
datasector  							DW 0x0000
cluster     							DW 0x0000

;*****************************************************************************
; FAT12_LoadRoot ()
; Load Root Directory Table
;*****************************************************************************
FAT12_LoadRoot:
	pusha							; store registers
	push	es

    ; find size of root directory as number of sectors      
	xor     cx, cx
 	xor     dx, dx
	mov     ax, 32
	mul     WORD [bpbRootEntries]
	div     WORD [bpbBytesPerSector]
	xchg    ax, cx

    ; find location of root directory     
	mov     al, BYTE [bpbNumberOfFATs]
	mul     WORD [bpbSectorsPerFAT]
	add     ax, WORD [bpbReservedSectors]
	mov     WORD [datasector], ax
	add     WORD [datasector], cx

    ; obtain the root directory 
 	push	word ROOT_SEG
	pop		es
	mov     bx, 0					
	call    readSectors
	pop		es
	
	popa
	ret

;*****************************************************************************
; FAT12_LoadFAT ()
; Loads FAT table
;
; Parameters: ES:DI => Root Directory Table
;*****************************************************************************
FAT12_LoadFAT:
	pusha
	push	es

    ; find the number of sectors used by FATs      
	xor     ax, ax
	mov     al, BYTE [bpbNumberOfFATs]
	mul     WORD [bpbSectorsPerFAT]
	mov     cx, ax

    ; find the location of FAT as sector number
	mov     ax, WORD [bpbReservedSectors]

    ; obtain the FAT
	push	word FAT_SEG
	pop		es
	xor		bx, bx
	call    readSectors
	pop		es
	
	popa
	ret
	
;*****************************************************************************
; FAT12_FindFile ()
; Search for filename in root table
;
; Parameters: DS:SI => File name
; Returns: AX => file index number in directory table. 
;   	   AX => -1 if error
;*****************************************************************************
FAT12_FindFile:
	push	cx
	push	dx
	push	bx
	mov	bx, si

    ; browse root directory for binary image
	mov     cx, WORD [bpbRootEntries]
	mov     di, ROOT_OFFSET
	cld

.FAT12_FindFile_fineNext:
	push    cx
	mov     cx, 11
	mov	si, bx
 	push    di
    repe  cmpsb
	pop     di
	je      .FAT12_FindFile_Found
	pop     cx
	add     di, 32
	loop    .FAT12_FindFile_fineNext

; failed to find the file
	pop	bx
	pop	dx
	pop	cx
	mov	ax, -1
	ret

.FAT12_FindFile_Found:
	pop	ax
	pop	bx
	pop	dx
	pop	cx
	ret

;*****************************************************************************
; FAT12_LoadFile ()
; Loads file to memory
;
; Parameters: ES:SI => name of the file which must be loaded
; 			  EBX:BP => where to load
;
; Returns: AX => -1 on error
;		   AX => 0 on success
; 		   CX => number of sectors read
;*****************************************************************************
FAT12_LoadFile:
	xor	ecx, ecx
	push	ecx

	push	bx
	push	bp
	call	FAT12_FindFile
	cmp	ax, -1
	jne	.FAT12_LoadFile_getStartingCluster
	pop	bp
	pop	bx
	pop	ecx
	mov	ax, -1
	ret

.FAT12_LoadFile_getStartingCluster:
	sub	edi, ROOT_OFFSET
	sub	eax, ROOT_OFFSET

	; get starting cluster
	push	word ROOT_SEG
	pop	es
	mov	dx, WORD [es:di + 0x001A]
	mov	WORD [cluster], dx
	pop	bx
	pop	es
	push    bx
	push	es
	call	FAT12_LoadFAT

.FAT12_LoadFile_readCluster:
	mov	ax, WORD [cluster]
	pop	es
	pop	bx
	
	; convert cluster to LBA
	sub     ax, 0x0002
    xor     cx, cx
    mov     cl, BYTE [bpbSectorsPerCluster]
    mul     cx
    add     ax, WORD [datasector]
	
	xor	cx, cx
	mov     cl, BYTE [bpbSectorsPerCluster]
	
	call	readSectors
	pop	ecx
	inc	ecx
	push	ecx
	push	bx
	push	es
	mov	ax, FAT_SEG
	mov	es, ax
	xor	bx, bx

	; get next cluster
	mov     ax, WORD [cluster]
	mov     cx, ax
	mov     dx, ax
	shr     dx, 0x0001
	add     cx, dx			; each entry in FAT is 12 bits long, one byte is 8 bits. Therefore, 1.5 times cluster number gives byte position.

	mov	bx, 0			
	add	bx, cx
	mov	dx, WORD [es:bx]
	test	ax, 0x0001
	jnz	.oddCluster

.evenCluster:
	and	dx, 0000111111111111b
	jmp	.done

.oddCluster:
	shr	dx, 0x0004

.done:
	mov	WORD [cluster], dx
	cmp	dx, 0x0ff0			; EOF
	jb	.FAT12_LoadFile_readCluster

	pop	es
	pop	bx
	pop	ecx
	xor	ax, ax
	ret





