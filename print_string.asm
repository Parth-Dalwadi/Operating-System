test_success:
	pusha
	mov bx, [0x11FF]
	cmp bx, 0xAA
	je success_message
	jne error_message
	popa
	ret

error_message:
	pusha
	mov ah, 0x0E
	mov bx, error
	call print_word
	popa
	ret

success_message:
	pusha
	mov bx, success
	call print_word
	popa
	ret

print_word:
	pusha
	mov ah, 0x0e

	print_loop:
		mov al, [bx]
		cmp al, 0
		je print_loop_done
		int 0X10
		add bx, 1
		jmp print_loop	

	print_loop_done:
		popa
		ret
