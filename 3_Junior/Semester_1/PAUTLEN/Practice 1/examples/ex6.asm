segment .data
	err_div_0 db "Division by 0", 0
	err_size db "Index vector out of range", 0
segment .bss
	__esp resd 64
	_m resb 1
segment .text
	global main
	extern scan_int, scan_boolean, print_int, print_boolean, print_blank, print_endofline, print_string
main:
	mov dword [__esp], esp
	mov dword eax, 0
	push dword eax
	pop dword eax
	mov dword [_m], eax
	mov dword eax, _m
	push dword eax
	mov dword eax, 5
	push dword eax
	pop dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	cmp ebx, eax
	mov dword ecx, 1
	jg end_great_1
	mov dword ecx, 0
end_great_1:
	push dword ecx
	pop dword eax
	cmp dword eax, 1
	jne end_then_1
	mov dword eax, 2
	push dword eax
	pop dword ebx
	push dword ebx
	call print_int
	add esp,4
	call print_endofline
	jmp end_then_else_1
end_then_1:
	mov dword eax, 3
	push dword eax
	pop dword ebx
	push dword ebx
	call print_int
	add esp,4
	call print_endofline
end_then_else_1:
	jmp end
error_div:
	push dword err_div_0
	call print_string
	add esp, 4
	call print_endofline
	jmp end
error_size:
	push dword err_size
	call print_string
	add esp, 4
	call print_endofline
end:
	mov dword esp, [__esp]
	ret
