
.data
msg0	BYTE "Fibonacci",0dh,0ah,"Charles Rymal",0dh,0ah,0
msg1	BYTE "Hello ",0
exit0	BYTE "number must be greater than 0",0dh,0ah,0
exit1	BYTE "number must be less than 47",0dh,0ah,0

f0	DWORD 1
f1	DWORD 0
counter	DWORD 0

.code

main PROC
	
	; welcome message
	
	; input
	call ReadInt
	mov  ecx,eax
	
	cmp  eax,1
	jl   exit_low_fibmax
	
	cmp  eax,46
	jg   exit_high_fibmax
	
	mov  ecx,eax
	
fib_loop:
	add  f0,f1
	mov  f0,f1
	mov  f1,eax
	
	call WriteInt
	
	
	
	loop fib_loop
	
	
exit_low_fibmax:
	mov  edx,OFFSET exit0
	call WriteString
	
	exit
exit_high_fibmax:
	mov  edx,OFFSET exit1
	call WriteString
	
	exit
	
main ENDP

END main



