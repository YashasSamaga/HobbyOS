;*****************************************************************************
; Bootloader (second stage)
;
; Code to obtain memory information from BIOS
; A20.inc
;*****************************************************************************
bits	16

;*****************************************************************************
; BiosGetMemoryMap
; Gets memory map entries from BIOS
;
; Parameters: ES:DI => address of the memory map array
; Returns: BP => number of entries
;
; Ends the boot loader in case of an error.
;
; Source: http://wiki.osdev.org/Detecting_Memory_(x86)#Getting_an_E820_Memory_Map
;*****************************************************************************
BiosGetMemoryMap:
	xor ebx, ebx
	xor bp, bp
	mov edx, 'PAMS'
	mov eax, 0xE820
	mov [es:di + 20], DWORD 1
	mov ecx, 24
	int 0x15
	jc UnsupBIOSfunctions
	mov edx, 'PAMS'
	cmp eax, edx
	jne UnsupBIOSfunctions
	test ebx, ebx
	je UnsupBIOSfunctions
	jmp short .jmpin
.e820lp:
	mov eax, 0xE820
	mov [es:di + 20], DWORD 1
	mov ecx, 24
	int 0x15
	jc short .e820f
	mov edx, 'PAMS'
.jmpin:
	jcxz .skipent
	cmp cl, 20
	jbe short .notext
	test byte [es:di + 20], 1
	je short .skipent
.notext:
	mov ecx, [es:di + 8]
	or ecx, [es:di + 12]
	jz .skipent
	inc bp
	add di, 24
.skipent:
	test ebx, ebx
	jne short .e820lp
.e820f:
	ret
	
;*****************************************************************************
; BiosGetMemorySize
; Gets lower and higher memory size
;
; Returns: AX => number of "contiguous" KB, 1M to 16M
;		   BX => "contiguous" 64KB pages above 16M
;
; Source: http://wiki.osdev.org/Detecting_Memory_(x86)#BIOS_Function:_INT_0x15.2C_AX_.3D_0xE801
;*****************************************************************************
BiosGetMemorySize:
	xor		ecx, ecx
	xor		edx, edx
	mov		ax, 0xE801
	int		0x15	
	jc		UnsupBIOSfunctions
	cmp		ah, 0x86
	je		UnsupBIOSfunctions
	cmp		ah, 0x80
	je		UnsupBIOSfunctions
	jcxz	.use_ax
	mov		ax, cx
	mov		bx, dx
.use_ax:
	ret
	
msgUnsupBIOS 			DB 0x0D, "The computer does not meet the system requirements (BIOS support).", 0x0A, 0x00
UnsupBIOSfunctions:
mov si, msgUnsupBIOS
call awaitKeypressAndReboot
cli
hlt

