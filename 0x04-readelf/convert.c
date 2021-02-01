#include "hreadelf.h"
/**
 * convertmsb - convert to big endian, switch pointer
 * @ptr: pointer to first octet of word
 * @size: size of type ptr points to
 */
void convertmsb(char *ptr, size_t size)
{
	size_t tmp, start, end;

	for (start = 0, end = size - 1; start < end; ++start, --end)
	{
		tmp = ptr[start];
		ptr[start] = ptr[end];
		ptr[end] = tmp;
	}
}


void convert(Elf64_Ehdr elf64, int ismsb)
{
	if (ismsb == 2)
	{
		convertmsb((char *) &elf64.e_type, sizeof(elf64.e_type));
		convertmsb((char *) &elf64.e_machine, sizeof(elf64.e_machine));
		convertmsb((char *) &elf64.e_version, sizeof(elf64.e_version));
		convertmsb((char *) &elf64.e_entry, sizeof(elf64.e_entry));
		convertmsb((char *) &elf64.e_phoff, sizeof(elf64.e_phoff));
		convertmsb((char *) &elf64.e_shoff, sizeof(elf64.e_shoff));
		convertmsb((char *) &elf64.e_flags, sizeof(elf64.e_flags));
		convertmsb((char *) &elf64.e_ehsize, sizeof(elf64.e_ehsize));
		convertmsb((char *) &elf64.e_phentsize, sizeof(elf64.e_phentsize));
		convertmsb((char *) &elf64.e_shstrndx, sizeof(elf64.e_phoff));
		convertmsb((char *) &elf64.e_phnum, sizeof(elf64.e_phnum));
		convertmsb((char *) &elf64.e_shnum, sizeof(elf64.e_shnum));
		convertmsb((char *) &elf64.e_shstrndx, sizeof(elf64.e_shstrndx));
	}
}
