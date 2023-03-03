[bits 16]
[org 0x7C00]
call boot_init
call kernel_load
call switch_to_32bit
jmp launch_kernel

%include "disk_read.asm"
%include "gdt.asm"
%include "print_string.asm"

boot_init:
	pop bx
	KERNEL_ADDRESS equ 0x1000
	mov bp, 0x9000
	mov sp, bp
	mov [BOOT_DRIVE], dl
	jmp bx

kernel_load:
	pusha
	call disk_test
	popa
	ret	
	
%include "switch_modes.asm"

[bits 16]
switch_to_32bit:
	cli
	lgdt [gdt_descriptor]
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	jmp CODE_SEGMENT_INDEX:begin_32bit_mode

[bits 32]	
launch_kernel:
	jmp KERNEL_ADDRESS
	mov ah, 0x0E
	mov bx, shutdown
	call print_word
	jmp $


	


success db "Success", 0
error db "Error", 0
shutdown db "OS has shut down", 0
BOOT_DRIVE db 0
times 510-($-$$) db 0  
dw 0xAA55
