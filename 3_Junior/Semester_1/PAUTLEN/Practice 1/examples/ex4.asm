segment .data
	err_div_0 db "Division by 0", 0
	err_size db "Vector index out of range", 0
segment .bss
	__esp resd 64
	_b1 resb 1
	_x resd 1
segment .text
	global main
	extern scan_int, scan_boolean, print_int, print_boolean, print_blank, print_endofline, print_string
main:
	mov dword [__esp], esp
	push _b1
	call scan_boolean
	add esp, 4
	push _x
	call scan_int
	add esp, 4
	mov dword eax, _x
	push dword eax
	mov dword eax, 3
	push dword eax
	pop dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	cmp ebx, eax
	mov dword ecx, 1
	jg end_great_0
	mov dword ecx, 0
end_great_0:
	push dword ecx
	pop dword ebx
	push dword ebx
	call print_boolean
	add esp,4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, 3
	push dword eax
	pop dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	cmp ebx, eax
	mov dword ecx, 1
	jge end_great_or_equal_1
	mov dword ecx, 0
end_great_or_equal_1:
	push dword ecx
	pop dword ebx
	push dword ebx
	call print_boolean
	add esp,4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, 3
	push dword eax
	pop dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	cmp ebx, eax
	mov dword ecx, 1
	jl end_less_2
	mov dword ecx, 0
end_less_2:
	push dword ecx
	pop dword ebx
	push dword ebx
	call print_boolean
	add esp,4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, 3
	push dword eax
	pop dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	cmp ebx, eax
	mov dword ecx, 1
	jle end_less_or_equal_3
	mov dword ecx, 0
end_less_or_equal_3:
	push dword ecx
	pop dword ebx
	push dword ebx
	call print_boolean
	add esp,4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, 3
	push dword eax
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	mov dword ecx, 1
	cmp eax, ebx
	je equal_4
	mov dword ecx, 0
equal_4:
	push dword ecx
	pop dword ebx
	push dword ebx
	call print_boolean
	add esp,4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, 3
	push dword eax
	pop dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	mov dword ecx, 1
	cmp eax, ebx
	jne etiq_5
	mov dword ecx, 0
etiq_5:
	push dword ecx
	pop dword ebx
	push dword ebx
	call print_boolean
	add esp,4
	call print_endofline
	mov dword eax, _b1
	push dword eax
	mov dword eax, 0
	push dword eax
	pop dword eax
	pop dword ebx
	and  eax, [ebx]
	push dword eax
	pop dword ebx
	push dword ebx
	call print_boolean
	add esp,4
	call print_endofline
	mov dword eax, _b1
	push dword eax
	mov dword eax, 1
	push dword eax
	pop dword eax
	pop dword ebx
	or eax, [ebx]
	push dword eax
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
