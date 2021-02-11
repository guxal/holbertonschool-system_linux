BITS 64
	global asm_putc	; export 'asm_putc' function

	section .text

asm_putc:  ; Function begin
        sub     rsp, 24             
        mov     edx, 1              
        lea     rsi, [rsp+0CH]      
        mov     dword [rsp+0CH], edi
        mov     edi, 1              
        mov rax, 1                  ; write syscall
        mov rsi, rsp                ; Character
        mov rdi, 1                  ; stdout
        mov rdx, 1                  ; one byte
        syscall           
        add     rsp, 24             
        ret                         
; asm_putc End of function
