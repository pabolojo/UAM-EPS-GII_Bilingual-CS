segment .data
	err_div_0 db "Division by 0", 0
	err_size db "The size of the array must be greater than 0 and less than tam_max", 0
segment .bss
	__esp resd 64
	_x resd 1
	_y resd 1
	_z resd 1
	_j resd 1
segment .text
	global main
	extern scan_int, scan_boolean, print_int, print_boolean, print_blank, print_endofline, print_string
main:
	mov dword [__esp], esp
	push _x
	call scan_int
	add esp, 4
	push _z
	call scan_int
	add esp, 4
	mov dword eax, _x
	push dword eax
	pop dword eax
	mov eax, [eax]
	neg eax
	push dword eax
	pop dword eax
	mov dword [_j], eax
	mov dword eax, _j
	push dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	push dword ebx
	call print_int
	add esp,4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, _z
	push dword eax
	pop dword eax
	pop dword ebx
	mov dword ecx, [ebx]
	sub ecx, [eax]
	push dword ecx
	pop dword ebx
	push dword ebx
	call print_int
	add esp,4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, 2
	push dword eax
	pop dword ebx
	pop dword ecx
	mov dword eax, [ecx]
	mov dword ecx, ebx
	cmp ecx, 0
	jne no_error
	jmp error_div
no_error:
	cdq
	idiv ecx
	push dword eax
	pop dword eax
	mov dword [_y], eax
	mov dword eax, _y
	push dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	push dword ebx
	call print_int
	add esp,4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, _y
	push dword eax
	pop dword eax
	pop dword ebx
	mov dword eax, [eax]
	mov dword ebx, [ebx]
	imul ebx
	push dword eax
	pop dword ebx
	push dword ebx
	call print_int
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
