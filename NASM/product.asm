; Natalia Durlik

	; AMD64 ABI
	; implements: extern "C" int iloczyn (int n, ...);
	; computes product of n arguments 

section .text

global iloczyn  
iloczyn: 
	; n=rdi rsi rdx rcx r8 r9
	pop r10 	; r10=ret
	push r9
	push r8
	push rcx
	push rdx
	push rsi
	
	mov rax, 1 ; wynik w rax
	mov rcx, 0 ; i
.lp:
	cmp rcx, rdi ; i<n
	jae .end
	xor rdx, rdx
	imul rax, [rsp+8*rcx]
	inc rcx
	jmp .lp
	
.end:
	 add rsp, 40 
	 push r10 	; ret
ret
