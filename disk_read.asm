disk_test:
	pusha
	mov ah, 0x02
	mov al, 0x1B
	mov bx, KERNEL_ADDRESS
	mov ch, 0x00
	mov cl, 0x02
	mov dh, 0x00
	mov dl, [BOOT_DRIVE]
	int 0x13
	jc error_message
	cmp al, 0x1B
	jne error_message	
	popa
	ret	
