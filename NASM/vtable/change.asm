
	; 64bit
	; extern "C" int zmien(A & a);
	; changing funtion in vtable to compute 3*n instead of n*n

section .data
	; vtable:
	ofset dq 0 ; dq wskazniki w 64bitowym
	type_info dq 0
	oblicz dq three_times_n
	
section .text

global zmien
zmien:
	; rdi- pointer to a
	; [rdi] pointer to vtable
	; [[rdi]] pointer to first virtual function
	
	mov rax, [rdi]
	mov rsi, type_info
	mov rax, [rax-8]
	mov [rsi], rax
	
	mov rax, [rdi]
	mov rsi, ofset
	mov rax, [rax-16]
	mov [rsi], rax
	
	
	mov rax, oblicz
	mov [rdi], rax
ret



three_times_n:
	; rdi - this
	; rsi - n
	imul esi, 3
	mov eax, esi
ret
