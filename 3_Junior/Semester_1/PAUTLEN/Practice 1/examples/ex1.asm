segment .data
	err_div_0 db "Division by 0", 0
	err_size db "The size of the array must be greater than 0 and less than tam_max", 0
segment .bss
	__esp resd 64
	_x resd 1
	_y resd 1
	_z resd 1
segment .text
	global main
	extern scan_int, scan_boolean, print_int, print_boolean, print_blank, print_endofline, print_string
main:
	mov dword [__esp], esp
	mov dword eax, 8
	push dword eax
	pop dword eax
	mov dword [_x], eax
	push _y
	call scan_int
	add esp, 4
	mov dword eax, _x
	push dword eax
	mov dword eax, _y
	push dword eax
	pop dword eax
	pop dword ebx
	mov dword ecx, [ebx]
	add ecx, [eax]
	push dword ecx
	pop dword eax
	mov dword [_z], eax
	mov dword eax, _z
	push dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	push dword ebx
	call print_int
	add esp,4
	call print_endofline
	mov dword eax, 7
	push dword eax
	mov dword eax, _y
	push dword eax
	pop dword eax
	pop dword ebx
	add ebx, [eax]
	push dword ebx
	pop dword eax
	mov dword [_z], eax
	mov dword eax, _z
	push dword eax
	pop dword ebx
	mov dword ebx, [ebx]
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
