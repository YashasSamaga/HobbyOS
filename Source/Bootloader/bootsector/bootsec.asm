;*****************************************************************************
; Bootsector (first stage of bootloader)
;
; bootsec.asm
;*****************************************************************************
bits	16
org	0

; irrespective of whether there is executable code in the bootsector, the
; jump code must always exist as some BIOSes and operating systems such as
; Windows look for jmp 'like' code in the first few bytes.
jmp main

;*****************************************************************************
; BIOS Parameter Block (BPB)
;
; BPB must begin from the 3rd byte of the bootsector.
; The far jump done previously is 3 bytes long.
;*****************************************************************************
bpbOEM									DB "LINDUSOS"		; must be 8 bytes long
bpbBytesPerSector  						DW 512
bpbSectorsPerCluster 					DB 1
bpbReservedSectors						DW 1
bpbNumberOfFATs 						DB 2
bpbRootEntries 							DW 224
bpbTotalSectors 						DW 2880
bpbMedia 								DB 0xF8
bpbSectorsPerFAT 						DW 9
bpbSectorsPerTrack 						DW 18
bpbHeadsPerCylinder 					DW 2
bpbHiddenSectors 						DD 0
bpbTotalSectorsBig     					DD 0
bsDriveNumber							DB 0
bsUnused 								DB 0
bsExtBootSignature 						DB 0x0029
bsSerialNumber	        				DD 0xABCD
bsVolumeLabel 	        				DB "LNDSOS FLPY" 	; must be 11 bytes long
bsFileSystem 	        				DB "FAT12   "		; must be 8 bytes long

;*****************************************************************************
; Defines
;*****************************************************************************

;-----------------------------------------------------------------------------
;  START	  END		  SIZE			        PURPOSE
;-----------------------------------------------------------------------------
; 0x00000 	0x003FF 	1KB 			- Interrupt Vector Table
; 0x00400 	0x004FF 	256 bytes 		- BIOS Data Area
; 0x00500 	0x07BFF 	almost 30 KB   	- FREE MEMORY
; 0x07C00  	0x07DFF 	512 bytes 		- bootsector (this code)
; 0x07E00 	0x7FFFF 	480.5 KB 		- FREE MEMORY
; 0x80000	0x9FFFF		121 KB			- Extended BIOS Data Area
; 0xA0000 	0xFFFFF		384 KB			- Video Memory, ROM Area

%define rootDirectoryClusterByteOffset 	0x001A
%define rootDirectoryFilenameLen 		0x000B
%define rootDirectoryEntrySize 			0x0020

%define rootDirectoryAddress			0x0200
%define FATAddress						0x0200
%define BTLSTG2SegmentAddress			0x0050 ; for segment register

;*****************************************************************************
; Data Declarations
;*****************************************************************************
CHSSector 								DB 0x0000
CHSHead   								DB 0x0000
CHSTrack  								DB 0x0000

rootDirectorySector  					DW 0x0000

cluster     							DW 0x0000
BTLSTG2_IMGNAME   						DB "BTLSTG2 BIN"

msgLoadFailure  						DB 0x0D, "BTLSTG2.BIN is missing.", 0x0A, 0x00
msgDiskFailure  						DB 0x0D, "Failed to read disk.", 0x0A, 0x00
msgAwaitKeypress  						DB 0x0D, "Press any key to restart.", 0x0A, 0x00

;*****************************************************************************
; puts
; Prints a string using BIOS interrupt 0x10
;
; Parameters: DS:SI => address of the null-terminated string
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
;
; Parameters: DS:SI => address of the null terminated error string
;*****************************************************************************
awaitKeypressAndReboot:
	call puts
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
; readSectors
; Reads sectors from a disk using BIOS interrupt 0x13
;
; Reads at least one sector even if CX is zero
;
; Parameters: CX => number of sectors to read
; 			  AX => where to read from (starting sector number)
; 			  ES:BX => destination address
;
; TO:DO reset drive trials
;*****************************************************************************
readSectors:
    .readSectors_nextSector:
		mov di, 0x05 							; 5 trials
	.readSectors_readSector:
		push	ax
		push    bx
		push    cx
		
	; convert LBA to CHS
		xor     dx, dx
		div     WORD [bpbSectorsPerTrack]
		inc     dl
		mov     BYTE [CHSSector], dl
		xor     dx, dx
		div     WORD [bpbHeadsPerCylinder]
		mov     BYTE [CHSHead], dl
		mov     BYTE [CHSTrack], al
		
		mov     ah, 0x02
		mov     al, 0x01
		mov     ch, BYTE [CHSTrack]            ; track
		mov     cl, BYTE [CHSSector]           ; sector
		mov     dh, BYTE [CHSHead]             ; head
		mov     dl, BYTE [bsDriveNumber]            ; drive
		int     0x13 
		jnc     .readSectors_readSectorDone			; attempt to read the next sector
		
	; failed to read the sector
		xor     ax, ax
		int     0x13
		dec 	di
		
		pop     cx
		pop     bx
		pop     ax
		jnz     .readSectors_readSector              ; attempt to read again
		
        mov     si, msgDiskFailure	
		call 	awaitKeypressAndReboot		
		cli
		hlt
		
    .readSectors_readSectorDone:
		pop     cx
		pop     bx
		pop     ax
		add		bx, WORD [bpbBytesPerSector]
		inc     ax
		loop    .readSectors_nextSector               
		ret

;*****************************************************************************
; Bootloader Entry Point
;*****************************************************************************
main:
	; bootsector is loaded at 0x7C00
	; assembler has been told that the origin is zero, hence adjust the segment registers
		cli
		mov		ax, 0x07C0 
		mov     ds, ax
		mov     es, ax

	; create the stack
		mov     ax, 0x00
		mov     ss, ax
		mov     sp, 0x7C00 ; use the space below the bootsector
		sti
	
	; clear the screen
		mov     ax, 0x03 ; AH = 0x00, AL = 0x03
		int     0x10		
		 
	; find size of root directory as number of sectors   
		xor     cx, cx
		xor     dx, dx
		mov     ax, rootDirectoryEntrySize
		mul     WORD [bpbRootEntries]	
		div     WORD [bpbBytesPerSector]	
		xchg ax, cx
		
	; find location of root directory
		mov     al, BYTE [bpbNumberOfFATs]
		mul     WORD [bpbSectorsPerFAT]
		add     ax, WORD [bpbReservedSectors]
		mov     WORD [rootDirectorySector], ax
		add     WORD [rootDirectorySector], cx
	
	; obtain the root directory
		mov     bx, rootDirectoryAddress
		call    readSectors

	; search for stage 2 file in the root directory
		mov     cx, WORD [bpbRootEntries]
		mov     di, rootDirectoryAddress
		cld
		
	.checkFileName:
		push    cx
		mov     cx, rootDirectoryFilenameLen
		mov     si, BTLSTG2_IMGNAME
		push    di
		repe	cmpsb
		pop     di
		je      .loadFAT
		pop     cx
		add     di, rootDirectoryEntrySize
		loop    .checkFileName
		
	; failed to find the file
		mov     si, msgLoadFailure
		call 	awaitKeypressAndReboot
		cli
		hlt
		
	; image found, load the image
    .loadFAT:
		mov     dx, WORD [di + rootDirectoryClusterByteOffset]
		mov     WORD [cluster], dx
          
	; find the number of sectors used by FATs   
		xor     ax, ax
		mov     al, BYTE [bpbNumberOfFATs]
		mul     WORD [bpbSectorsPerFAT]
		mov     cx, ax

	; find the location of FAT as sector number
		mov     ax, WORD [bpbReservedSectors]
          
	; obtain a FAT
		mov     bx, FATAddress
		call    readSectors

	; set image file load address
        mov     ax, BTLSTG2SegmentAddress
        mov     es, ax
        mov     bx, 0x00
        push    bx

    .readCluster:     
		mov     ax, WORD [cluster]
		pop     bx
		
	; convert cluster to LBA
		sub     ax, 0x02
		xor     cx, cx
		mov     cl, BYTE [bpbSectorsPerCluster]
		mul     cx
		add     ax, WORD [rootDirectorySector]
	
		xor     cx, cx
		mov     cl, BYTE [bpbSectorsPerCluster]
		call    readSectors
		push    bx
          
	; get next cluster     
		mov     ax, WORD [cluster]
		mov     cx, ax
		mov     dx, ax
		shr     dx, 0x01
		add     cx, dx					; each entry in FAT is 12 bits long, one byte is 8 bits. Therefore, 1.5 times cluster number gives byte position.
		mov     bx, FATAddress
		add     bx, cx
		mov     dx, WORD [bx]
		test    ax, 0x01
		jnz     .oddCluster
          
    .evenCluster:     
		and     dx, 0000111111111111b
		jmp     .done
         
    .oddCluster:     
		shr     dx, 0x0004
       
	.done:
		mov     WORD [cluster], dx
		cmp     dx, 0x0FF0
		jb      .readCluster             
	
		jmp BTLSTG2SegmentAddress:0x00
		
TIMES 510-($-$$) DB 0
DW 0xAA55