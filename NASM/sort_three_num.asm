;Natalia Durlik
section .text

	; 32 bit C standard 
	; implements function void sortuj( int * a, int *b, int * c);
	; sorts 3 numbers in descending order

global sortuj  
sortuj: 
	push 	ebp ; ramka stosu
	mov 	ebp, esp
	push 	ebx
	
	mov 	eax, [ebp+8]
	mov 	ebx, [eax]
	mov 	ecx, [ebp+12]
	mov 	edx, [ecx]
	cmp 	ebx, edx ; if(a<b) swap(a,b)
	jge 	.j1 
	mov 	[eax], edx
	mov 	[ecx], ebx
.j1:
	mov 	eax, [ebp+8]
	mov 	ebx, [eax]
	mov 	ecx, [ebp+16]
	mov 	edx, [ecx]
	cmp 	ebx, edx 
	jge 	.j2
	mov 	[eax], edx
	mov 	[ecx], ebx
.j2:
	mov 	eax, [ebp+12]
	mov 	ebx, [eax]
	mov 	ecx, [ebp+16]
	mov 	edx, [ecx]
	cmp 	ebx, edx 
	jge 	.j3
	mov 	[eax], edx
	mov 	[ecx], ebx
.j3:
	
	
	pop 	ebx
	mov 	esp, ebp
	pop 	ebp
ret




