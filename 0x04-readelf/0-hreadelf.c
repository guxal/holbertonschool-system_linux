#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <elf.h>


int printdata(char *ident, char *str)
{
	if (ident[EI_DATA] == ELFDATANONE)
	{
		fprintf(stderr, "Error");
		return (1);
	}
	if (ident[EI_DATA] == ELFDATA2LSB)
	{
		printf("%6s%-31c%s%s\n", "Data", ':', "2's complement, ",
				"little endian");
	}
	else
	{
		printf("%6s%-31c%s%s\n", "Data", ':', "2's complement, ",
				"big endian");
	}
	return (0);
}

int printclass(char *ident, char *str)
{
	if (ident[EI_CLASS] == ELFCLASSNONE)
	{
		fprintf(stderr, "Error");
		return (1);
	}
	if (ident[EI_CLASS] == ELFCLASS32)
	{
		printf("%7s%-30c%s\n", "Class", ':', "ELF32");
	}
	else
	{
		printf("%7s%-30c%s\n", "Class", ':', "ELF64");
	}
	return (0);
}

void _printmag(char *ident)
{
	size_t i;

	printf("%11s", "Magic:   ");
	for (i = 0; i < EI_NIDENT; ++i)
		printf("%02x ", ident[i]);
	putchar('\n');
}




//---------------------------------------

FILE *get_fd(char *name)
{
	FILE *fp;
	struct stat sb;

	fp = fopen(name, "rb");

	if (!fp)
	{
		fprintf(stderr, "%s: Error: '%s': No such file\n", "no", name);
		return (NULL);
	}

	return (fp);
}


int valid_args(int argc, char **argv)
{
	int status;

	status = 1;
	if (argc != 2)
	{
		fprintf(stderr, "%s: Warning: Nothing to do.\n"
						"Usage: %s elf-file\n", *argv, *argv);
		return (0);
	}

	return (status);
}

int printelfh(FILE *fp, char *args)
{
	Elf64_Ehdr elf64;
	Elf32_Ehdr elf32;
	int exit_stat;

	fread(&elf64, sizeof(elf64), 1, fp);
	rewind(fp);
	fread(&elf32, sizeof(elf32), 1, fp);
	if (memcmp(elf64.e_ident, ELFMAG, SELFMAG))
	{
		fprintf(stderr, "Error");
		return (1);
	}
	puts("ELF Header:");
	_printmag(elf64.e_ident);
	exit_stat = printclass(elf64.e_ident, args);
	if (exit_stat)
		return (1);
	exit_stat = printdata(elf64.e_ident, args);
		return (1);
	return (exit_stat);
}


/**
 * main - read elf file
 * @argc: the count of args
 * @argv: the args
 */
int main(int argc, char **argv)
{
	FILE *fp;
	int exit_stat;
	Elf64_Ehdr elf64;
	size_t test;

	if (valid_args(argc, argv) == 0)
		return (1);

	fp = get_fd(argv[1]);

	if (!fp)
		return (1);


//	test = fread(&elf64, sizeof(elf64.e_ident), 1, fp);
//	printf("%li\n", test);
	exit_stat = printelfh(fp, *argv);
	return (exit_stat);
}

/*
int main(int argc, char **argv)
{
	FILE *fp;
	int exit_stat;
	Elf64_Ehdr elf64;
	Elf32_Ehdr elf32;
	size_t test;
	size_t i;

	fp = fopen(argv[1], "rb");
	test = fread(&elf64, sizeof(elf64.e_ident), 1, fp);

	printf("%li\n", test);
	test = fread(&elf32, sizeof(elf32.e_ident), 1, fp);
	printf("%li\n", test);
	test = ftell(fp);
	rewind(fp);
	printf("%li\n", test);
	for(i = 0; i < EI_NIDENT; ++i)
	//fp = parse_args(argc, argv);
		printf("%02x ", elf64.e_ident[i]);
	printf("\n");
	printf("%s\n", elf64.e_ident);
	printf("%s %d\n", ELFMAG, SELFMAG);
//if (!fp)
	printf("version: %d\n", EI_VERSION);
	//	return (1);
	printf("EI_OSABI: %d\n", EI_OSABI);
	exit_stat = 1;*/
	/* exit_stat = printelfh(fp, *argv); */
	/*return (exit_stat);
}*/

