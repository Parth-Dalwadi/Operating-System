[bits 32]
begin_32bit_mode:
	mov ax, DATA_SEGMENT_INDEX
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ebp, 0x90000
	mov esp, ebp
	jmp KERNEL_ADDRESS	
