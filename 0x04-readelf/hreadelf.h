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

/* printelf_1 */
void printinstruction(instruction_t instruct[], int size, Elf64_Half match);
void printmachine(Elf64_Half machine);
void printtype(Elf64_Half type);
void printosabi(char *ident);
/* printelf_0 */
int printversion(char *ident, char *str);
int printdata(char *ident, char *str);
int printclass(char *ident, char *str);
void _printmag(char *ident);

#endif
