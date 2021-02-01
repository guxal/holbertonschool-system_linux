#ifndef HREADELF_H
#define HREADELF_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <elf.h>

/**
 * struct instruction_s - code and str
 * @code: the byte code
 * @str: string to print
 *
 * Description: code and str
 * for hreadelf HOLBERTON
 */
typedef struct instruction_s
{
	int code;
	char *str;
} instruction_t;

/* printelf_3 */
void printshstrndx(Elf64_Half shstrndx64);
void printshnum(Elf64_Half shnum64);
void printshentsize(Elf64_Half shentsize64);
void printphnum(Elf64_Half phnum64);
/* printelf_2 */
void printhdrsize(Elf64_Ehdr elf64);
void printflags(Elf64_Word flags64);
void printpshoff(Elf64_Ehdr elf64);
void printentry(Elf64_Addr entry64);
void printfileversion(Elf64_Word version);
/* printelf_1 */
void printinstruction(instruction_t instruct[], int size, Elf64_Half match);
void printmachine(Elf64_Half machine);
void printtype(Elf64_Half type);
void printosabi(unsigned char *ident);
/* printelf_0 */
int printversion(unsigned char *ident, char *str);
int printdata(unsigned char *ident, char *str);
int printclass(unsigned char *ident, char *str);
void _printmag(unsigned char *ident);

#endif
