; Natalia Durlik

	; 32bit C standard
	; dot product
	; implements function: extern "C" long double iloczyn_skalarny(int n, long double * x, long double * y);

section .text

global iloczyn_skalarny  
iloczyn_skalarny: 
	push 	ebp
	mov 	ebp, esp
	
	;%define 	n dword [ebp+8] 
	mov 	eax, dword [ebp+8]
	cdq
	imul 	eax, 12
	mov 	ecx, eax ; indeks
	mov 	eax, [ebp+12] ; adresy tablic
	mov 	edx, [ebp+16]
	
	; assuming n>0
	
	fld 	tword [eax+ecx-12] ; tword - ten bytes, long double (80)
	fld 	tword [edx+ecx-12]
	fmulp 	ST1, ST0

.lp:
	add 	ecx, -12
	jz 		.end
	fld 	tword [eax+ecx-12]
	fld 	tword [edx+ecx-12]
	fmulp 	ST1, ST0
	faddp 	ST1, ST0
	jmp 	.lp
	
.end:
	
	mov 	esp, ebp
	pop 	ebp
ret 
	
