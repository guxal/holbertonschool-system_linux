global asm_strlen

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

