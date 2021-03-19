; Natalia Durlik

	; 32 bit
	; extern "C" void minmax(int n, int * tab, int * max, int * min);
	; using SSE min and max


section .data
	max dd 0,0,0,0
	min dd 0,0,0,0

section .text

global minmax 
minmax:
	push ebx
	mov eax, [esp+8] ; n>0, n%4==0
	mov ebx, [esp+12]
	
	movups xmm0, [ebx] ; max
	movups xmm1, [ebx] ; min
	
	.lp:
		sub eax, 4
		cmp eax, 0
		jle .end
		
		add ebx, 16
		
		movups xmm2, [ebx]
		movups xmm3, [ebx]
		
		pmaxsd xmm0, xmm2
		pminsd xmm1, xmm3
		
	jmp .lp

.end:

	movups [max], xmm0
	movups [min], xmm1
	mov eax, [max]
	mov ebx, [max+4]
	mov edx, [min]
	mov ecx, [min+4]
	
	cmp eax, [max+8]
	cmovl eax, [max+8]
	
	cmp ebx, [max+12]
	cmovl ebx, [max+12]
	
	cmp edx, [min+8]
	cmovg edx, [min+8]
	
	cmp ecx, [min+12]
	cmovg ecx, [min+12]
	
	cmp eax, ebx
	cmovl eax, ebx
	
	cmp edx, ecx
	cmovg edx, ecx
	
	
	mov ebx, [esp+16]
	mov [ebx], eax
	mov ecx, [esp+20]
	mov [ecx], edx
	
	pop ebx
ret

