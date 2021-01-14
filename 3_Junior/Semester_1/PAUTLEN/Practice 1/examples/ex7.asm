segment .data
	err_div_0 db "Division by 0", 0
	err_size db "Index vector out of range", 0
segment .bss
	__esp resd 64
	_z resb 1
segment .text
	global main
	extern scan_int, scan_boolean, print_int, print_boolean, print_blank, print_endofline, print_string
_doble:
	push ebp
	mov ebp, esp
	sub dword esp, 4
	lea eax, [ebp+8]
	push dword eax
	lea eax, [ebp - 4]
	push dword eax
	pop dword eax
	pop dword ebx
	mov ebx, [ebx]
	mov [eax], ebx
	mov dword eax, 2
	push dword eax
	lea eax, [ebp+8]
	push dword eax
	pop dword eax
	pop dword ebx
	mov dword eax, [eax]
	imul ebx
	push dword eax
	pop dword eax
	mov esp, ebp
	pop dword ebp
	ret
main:
	mov dword [__esp], esp
	mov dword eax, 2
	push dword eax
	pop dword eax
	mov dword [_z], eax
	mov dword eax, _z
	push dword eax
	pop dword eax
	mov eax, [eax]
	push dword eax
	call _doble
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
