;*****************************************************************************
; Bootloader (second stage)
;
; A20 Gate Enabler
; A20.inc
;*****************************************************************************
bits	16

;*****************************************************************************
; Data Declaration
;*****************************************************************************
msgA20EnableFailure DB "Fatal Error: BTLSGT2 failed to enable A20 gate.", 0x0A, 0x00	

;*****************************************************************************
; statusA20
;
; Purpose: to check the status of the a20 line in a completely self-contained state-preserving way.
;          The function can be modified as necessary by removing push's at the beginning and their
;          respective pop's at the end if complete self-containment is not required.
;
; Requirements: Interrupts MUST be disabled (buggy 8086/8088 processors will triple fault)
;
; Returns: 0 in ax if the a20 line is disabled (memory wraps around)
;          1 in ax if the a20 line is enabled (memory does not wrap around)
;
; Source: http://wiki.osdev.org/A20_Line
;*****************************************************************************
statusA20:
	cli
    push ds
    push es
 
    xor ax, ax ; ax = 0
    mov es, ax
 
    mov ax, 0xFFFF
    mov ds, ax
 
    mov di, 0x0500
    mov si, 0x0510
 
    mov al, BYTE [es:di]
    push ax
 
    mov al, BYTE [ds:si]
    push ax
 
    mov BYTE [es:di], 0x00
    mov BYTE [ds:si], 0xFF
 
    cmp BYTE [es:di], 0xFF
 
    pop ax
    mov BYTE [ds:si], al
 
    pop ax
    mov BYTE [es:di], al
 
    mov ax, 0
    je .statusA20Done
 
    mov ax, 1
 
.statusA20Done:
    pop es
    pop ds 
	sti
    ret

;*****************************************************************************
; EnableA20
;
;
; Attempts to enable A20 gate using different methods until success.
; If the function fails to enable the A20 gate, it forces a hard reboot.
;*****************************************************************************
EnableA20:	
; check if A20 gate is already enabled
	call statusA20
	or ax, ax
	jnz EnableA20Done
	
; check if BIOS supports A20 interrupts (INT 0x15)
	mov     ax, 0x2403
	int     0x15
	jc      .EnableA20_KB_OutputPort        ; INT 0x015 is not supported
	
	cmp     ah, 0
	jnz     .EnableA20_KB_OutputPort       	; INT 0x15 is not supported
	 
; Try activating the A20 Gate
	mov     ax, 0x2401                		
	int     0x15
	jc      .EnableA20_KB_OutputPort     	; failed to activate the gate
	cmp     ah, 0
	jnz     .EnableA20_KB_OutputPort     	; failed to activate the gate

.EnableA20_KB_OutputPort:
; try enabling using keyboard output port
	cli
	
	; disable keyboard
    call    wait_input
    mov     al,0xAD
	out     0x64,al		
	call    wait_input

	; tell controller to read output port
	mov     al,0xD0
	out     0x64,al		
	call    wait_output

	; get output port data and store it
	in      al,0x60
	push    eax		
	call    wait_input

	; tell controller to write output port
	mov     al,0xD1
	out     0x64,al		
	call    wait_input

	; set A20 bit and write to output port
	pop     eax
	or      al,2		
	out     0x60,al

	; enable keyboard
	call    wait_input
	mov     al,0xAE
	out     0x64,al

	call    wait_input

    call statusA20	
	or ax, ax
	jnz EnableA20Done
	
; try enabling using keyboard command port
	mov	al, 0xdd	; enable A20 command
	out	0x64, al
	
	call statusA20
	or ax, ax
	jnz EnableA20Done

; try using system port
	push	ax
	mov	al, 2
	out	0x92, al
	pop	ax
	
	call statusA20
	or ax, ax
	jnz EnableA20Done

; all attempts to enable A20 gate failed
	mov si, msgA20EnableFailure
	call awaitKeypressAndReboot
	cli
	hlt
	
wait_input:
        in      al,0x64
        test    al,2
        jnz     wait_input
        ret

wait_output:
        in      al,0x64
        test    al,1
        jz      wait_output
        ret
		
EnableA20Done: 
	ret

