#include "readelf.h"
/**
 * elf_check_file - checks if the elf file is valid
 * @magic: magic string
 * Return: on success: true, on Failure: false.
 */
bool elf_check_file(unsigned char *magic)
{
	if (magic[0] != ELFMAG0 || magic[1] != ELFMAG1
		|| magic[2] != ELFMAG2 || magic[3] != ELFMAG3)
		return (false);
	return (true);
}
/**
 * get_architecture - fetches the architecture of the elf file
 * @c: char
 * @arch: architecture - 32 / 64
 * Return: on success: true, on Failure: false.
 */
bool get_architecture(char c, int *arch)
{
	if (c == ELFCLASS32)
		*arch = 32;
	else if (c == ELFCLASS64)
		*arch = 64;
	else
		return (false);
	return (true);
}

/**
 * main - A program that takes the name of a elf files as a parameter and
 * displays the information contained in symbol tables of an ELF file.
 * @argc: no of inputs.
 * @argv: inputs.
 *
 * Return: on success: 0, on Failure: 1.
 */
int main(int argc, char *argv[])
{
	ElfN_Ehdr ehdr;
	int exit_status = 0, arch = 0;
	FILE *file;

	/* validate user input */
	if (argc < 2)
	{
		printf("Usage: %s elf_filename\n", argv[0]);
		exit(1);
	}
	/* open the elf file */
	file = fopen(argv[1], "rb");
	if (file)
	{
		if (fread(ehdr.e_ident, EI_NIDENT, 1, file) &&
			elf_check_file(ehdr.e_ident))
		{
			get_architecture(ehdr.e_ident[EI_CLASS], &arch);
			if (!read_elf_stN(&ehdr, file, arch))
				fprintf(stderr, "%s: %s: no symbols\n", argv[0], argv[1]);
		} else
			printf("%s: %s\n", E, argv[0]);
		exit_status = 1;
		fclose(file);
	} else
	{
		printf("%s: Error: '%s': No such file\n", argv[0], argv[1]);
		exit_status = 1;
	}
	return (exit_status);
}
