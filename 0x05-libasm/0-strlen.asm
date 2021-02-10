BITS 64
	global asm_strlen	; export 'asm_strlen' function

section .text

asm_strlen:
	xor		eax, eax
	cmp		byte [rdi+rax], 0
	jz		?_002

?_001:
	add		rax, 1
	cmp		byte [rdi+rax], 0
	jnz		?_001
?_002:
	ret

; vi: set noet ft=nasm sts=0 sw=8 ts=8
