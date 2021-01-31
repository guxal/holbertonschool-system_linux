#ifndef HREADELF_H
#define HREADELF_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <elf.h>

typedef struct instruction_s
{
	int code;
	char *str;
} instruction_t;

#endif
