# Assembly

> ## [Intro to x86 Assembly Language (Part 1)](https://www.youtube.com/watch?v=wLXIWKUWpSs)

## Requirements

install nasm for compiling asm

```bash
$ sudo apt-get install nasm
```


## Compile examples with nasm and ld

```bash
$ nasm -f elf32 ex1.asm -o ex1.o

$ ld -m elf_i386 ex1.o -o ex1
```

## Disassemble

`file:` ex1.asm
```c
global _start
_start:
      mov eax, 1
      mov ebx, 42
      int 0x80
```

> after compiling

```bash
$ gdb ./ex1

(gdb) disas /m _start
Dump of assembler code for function _start:
   0x08048060 <+0>:     mov    $0x1,%eax
   0x08048065 <+5>:     mov    $0x2a,%ebx
   0x0804806a <+10>:    int    $0x80
```

> the value ``$0x2a`` is **42** in decimal



`options:` **disas** 

```bash
disassemble
disassemble /m
disassemble /s
disassemble /r

# MESSAGE
specify a range of addresses to dump, in one of two forms:

start,end
the addresses from start (inclusive) to end (exclusive)

start,+length
the addresses from start (inclusive) to start+length (exclusive).

The argument(s) can be any expression yielding a numeric value, such as ‘0x32c4’, ‘&main+10’ or ‘$pc - 8’.

ex:
(gdb) disas 0x32c4, 0x32e4
Dump of assembler code from 0x32c4 to 0x32e4:
   0x32c4 <main+204>:      addil 0,dp
   0x32c8 <main+208>:      ldw 0x22c(sr0,r1),r26
   0x32cc <main+212>:      ldil 0x3000,r31
   0x32d0 <main+216>:      ble 0x3f8(sr4,r31)
   0x32d4 <main+220>:      ldo 0(r31),rp
   0x32d8 <main+224>:      addil -0x800,dp
   0x32dc <main+228>:      ldo 0x588(r1),r26
   0x32e0 <main+232>:      ldil 0x3000,r31
End of assembler dump
```

## Using 

```bash
$ ./ex1

$ echo $?
42
```

## SUB

```c
global _start
_start:
      mov eax, 1
      mov ebx, 42
      sub ebx, 29 // <----------- this line
      int 0x80
```

```bash
$ ./ex1

$ echo $?
13
```


## Operation [operands, ...]

```s
mov ebx, 123    ; ebx = 123
mov eax, ebx    ; eax = ebx
add ebx, ecx    ; ebx += ecx
sub ebx, edx    ; ebx -= edx
mul ebx         ; eax *= ebx
div edx         ; eax /= edx

```


## Test2

`file:` ex2.asm
````asm
global _start

section .data
    msg db "Hello, world!", 0x0a
    len equ $ - msg

section .text
_start:
    mov eax, 4      ; sys_write system call
    mov ebx, 1      ; stdout file descriptor
    mov ecx, msg    ; bytes to write
    mov edx, len    ; number of bytes to write
    int 0x80        ; perform system call
    mov eax, 1      ; sys_exit system call
    mov ebx, 0      ; exit status is 0
    int 0x80
````
- disassemble 
```bash
(gdb) disas /m _start
Dump of assembler code for function _start:
   0x08048080 <+0>:     mov    $0x4,%eax
   0x08048085 <+5>:     mov    $0x1,%ebx
   0x0804808a <+10>:    mov    $0x80490a4,%ecx
   0x0804808f <+15>:    mov    $0xe,%edx
   0x08048094 <+20>:    int    $0x80
   0x08048096 <+22>:    mov    $0x1,%eax
   0x0804809b <+27>:    mov    $0x0,%ebx
   0x080480a0 <+32>:    int    $0x80

(gdb) x/s 0x80490a4 # view string Hello, World!
"Hello, world!\n"<error: Cannot access memory at address 0x80490b2>
(gdb) x/s 0x0804808a
0x804808a <_start+10>:  "\271\244\220\004\b\272\016"
(gdb) print msg
$5 = 1819043144
```



## Other commands gdb

```bash
(gdb) info line _start
(gdb) info registers
(gdb) x/i $pc # -> registers
(gdb) bt -> stack
(gdb) info sharelibrary # -> libraries
(gdb) x/s address # -> print string in memory
(gdb) x/5 address # -> print assembly in memory
```

## References
- [machine_code sourceware.org](https://sourceware.org/gdb/download/onlinedocs/gdb/Machine-Code.html)
- [assembly language debugging](https://mohit.io/blog/gdb-assembly-language-debugging-101/)
- [examining memory MIT](http://web.mit.edu/gnu/doc/html/gdb_10.html)

