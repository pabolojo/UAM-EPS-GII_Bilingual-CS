segment .data
	err_div_0 db "Division by 0", 0
	err_size db "Index vector out of range", 0
segment .bss
	__esp resd 64
	_m resb 1
	_v resb 4
segment .text
	global main
	extern scan_int, scan_boolean, print_int, print_boolean, print_blank, print_endofline, print_string
main:
	mov dword [__esp], esp
	mov dword eax, 0
	push dword eax
	pop dword eax
	mov dword [_m], eax
while_start_1:
	mov dword eax, _m
	push dword eax
	mov dword eax, 4
	push dword eax
	pop dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	cmp ebx, eax
	mov dword ecx, 1
	jle end_less_or_equal_1
	mov dword ecx, 0
end_less_or_equal_1:
	push dword ecx
	pop dword eax
	cmp dword eax, 1
	jne end_while_1
	mov dword eax, _m
	push dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	push dword ebx
	call print_int
	add esp,4
	call print_endofline
	mov dword eax, _m
	push dword eax
	mov dword eax, 10
	push dword eax
	pop dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	imul ebx
	push dword eax
	mov dword eax, _m
	push dword eax
	pop dword eax
	mov eax, [eax]
	cmp eax, 0
	jl error_size
	cmp eax, 4
	jge error_size
	mov dword ebx, _v
	mov dword ebx, _v
	lea eax,[ebx + eax*4]
	push dword eax
	pop dword eax
	pop dword ebx
	mov [eax], ebx
	mov dword eax, _m
	push dword eax
	mov dword eax, 1
	push dword eax
	pop dword eax
	pop dword ebx
	add eax, [ebx]
	push dword eax
	pop dword eax
	mov dword [_m], eax
	jmp while_start_1
end_while_1:
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
