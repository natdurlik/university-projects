section .text            

global _start            
                 ; computes sum of two digits
_start:
	; first string
	mov     rax, 1      
	mov     rdi, 1 
	mov     rsi, t1      
	mov     rdx, size_t1
	syscall 

	; first number
	mov 	rax, 0 			
	mov 	rdi, 0 			
	mov 	rsi, num1	
	mov 	rdx, 2 		
	syscall						

	; second number
	mov 	rax, 0 			
	mov 	rdi, 0 			
	mov 	rsi, num2	
	mov 	rdx, 2	
	syscall	
	  
	; second string
	mov     rax, 1      
	mov     rdi, 1 
	mov     rsi, t2     
	mov     rdx, size_t2
	syscall 
	

	mov 	al, [num1]	 
	mov 	bl, [num2]
	sub 	al, '0' 	 ; ASCII to digit
	sub 	bl, '0'
	add 	al, bl		 
	
	cmp 	ax, 10 		 
	jl _cyfraJednosci 	 
	mov 	byte [wynik], '1'
	sub 	ax, 10
	
_cyfraJednosci:
	add 	al, '0' 
	mov 	[wynik+1], al
	
	; wypisanie wyniku
	mov     rax, 1      
	mov     rdi, 1 
	mov     rsi, wynik     
	mov     rdx, 3
	syscall 

	; zakonczenie programu
	mov     rax, 60         
	mov     rdi, 0         
	syscall                 

section .data    
	t1 db "Podaj dwie cyfry",10
	size_t1 equ $-t1
	t2 db "Wynik dodawiania wynosi:",10
	size_t2 equ $-t2
	atest db 0,10
	wynik db "  ",10 	; przygotowane miejsce na wynik z obliczen

section .bss
	num1 resb 1
	num2 resb 1
