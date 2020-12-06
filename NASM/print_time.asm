section .text            

global _start            
                 ; read sys time and print     
_start:
	mov 	rax, 201		; sys_time
							
	syscall 				; returns seconds since 1970


	mov 	edx, 0
	mov 	ebx, 86400
	div 	ebx
	mov 	eax, edx
	
	; sekundy
	mov 	edx, 0
	mov 	ebx, 10
	div 	ebx 		; reszta z dzielenia zapisuje sie w edx, a wynik w eax
	add 	dl, '0'
	mov 	[time+7], dl ; wstawiamy cyfre jednosci dla sekund
	
	mov 	edx, 0
	mov 	ebx, 6
	div 	ebx
	add 	dl, '0'
	mov 	[time+6], dl
	
	; minuty
	mov 	edx, 0
	mov 	ebx, 10
	div 	ebx
	add 	dl, '0'
	mov 	[time+4], dl
	
	mov 	edx, 0
	mov 	ebx, 6
	div 	ebx
	add 	dl, '0'
	mov 	[time+3], dl


	; wynik jest o 2h za maly, poniewaz odczytalismy czas UTC
	inc eax
	inc eax
	
	; godziny
	mov 	edx, 0
	mov 	ebx, 10
	div 	ebx
	add 	dl, '0'
	mov 	[time+1], dl
	
	mov 	edx, 0
	mov 	ebx, 2
	div 	ebx
	add 	dl, '0'
	mov 	[time+0], dl
	
	
	; wyswietlamy aktualny czas
	mov 	rax, 1
	mov 	rdi, 1
	mov 	rsi, time
	mov 	rdx, size_time
	syscall
	
	; zakonczenie programu
	mov     rax, 60         
	mov     rdi, 0         
	syscall 
	
	
section .data
	time db "XX:XX:XX",0ah 	 ; time template
	size_time equ $ - time
	

