;*****************************************************************************
; Bootloader (second stage)
; Real Mode Floppy Interface BIOS Routines
;	
; floppy16.asm
;*****************************************************************************
bits	16

;*****************************************************************************
; Data Declarations
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

CHSSector 								DB 0x00
CHSHead   								DB 0x00
CHSTrack  								DB 0x00

msgDiskFailure  						DB 0x0D, "Failed to read disk.", 0x0A, 0x00

;*****************************************************************************
; readSectors
; Reads sectors from a disk using BIOS interrupt 0x13
;
; Reads at least one sector even if CX is zero
;
; CX => number of sectors to read
; AX => where to read from (starting sector number)
; ES:BX => destination address
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
        call    puts		
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