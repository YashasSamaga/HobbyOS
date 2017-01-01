%ifndef __32CONTROL_INC_INCLUDED__
%define __32CONTROL_INC_INCLUDED__

%include "Loader\common.inc"
bits 32

loadkernel:
mov	ax, DATA_DESC	
mov	ds, ax
mov	ss, ax
mov	es, ax
mov	esp, 90000h	

CopyImage:
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



%endif
