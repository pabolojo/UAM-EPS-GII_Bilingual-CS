segment .data
	err_div_0 db "Division by 0", 0
	err_size db "The size of the array must be greater than 0 and less than tam_max", 0
segment .bss
	__esp resd 64
	_b1 resb 1
segment .text
	global main
	extern scan_int, scan_boolean, print_int, print_boolean, print_blank, print_endofline, print_string
main:
	mov dword [__esp], esp
	push _b1
	call scan_boolean
	add esp, 4
	mov dword eax, _b1
	push dword eax
	pop dword eax
	mov eax, [eax]
	cmp dword eax, 0
	je zero_0
	mov dword ebx, 0
	jmp end_no_0
zero_0:
	mov dword ebx, 1
end_no_0:
	push dword ebx
	pop dword ebx
	push dword ebx
	call print_boolean
	add esp,4
	call print_endofline
	mov dword eax, _b1
	push dword eax
	pop dword eax
	mov eax, [eax]
	cmp dword eax, 0
	je zero_1
	mov dword ebx, 0
	jmp end_no_1
zero_1:
	mov dword ebx, 1
end_no_1:
	push dword ebx
	pop dword eax
	cmp dword eax, 0
	je zero_2
	mov dword ebx, 0
	jmp end_no_2
zero_2:
	mov dword ebx, 1
end_no_2:
	push dword ebx
	pop dword ebx
	push dword ebx
	call print_boolean
	add esp,4
	call print_endofline
	jmp end
error_div:
	push dword err_div_0
	call print_string
	add esp, 4
	jmp end
error_size:
	push dword err_size
	call print_string
	add esp, 4
end:
	mov dword esp, [__esp]
	ret
