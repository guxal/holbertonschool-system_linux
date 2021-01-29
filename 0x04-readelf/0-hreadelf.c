#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <elf.h>


FILE *parse_args(int argc, char **argv)
{
	FILE *fp;
	struct stat sb;

	if (argc != 2)
	{
		fprintf(stderr, "%s: Warning: Nothing to do.\n"
						"Usage: %s elf-file\n", *argv, *argv);
		return (NULL);
	}

	return (NULL);
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
	size_t i;

	fp = fopen("/bin/pwd", "rb");
	test = fread(&elf64, sizeof(elf64.e_ident), 1, fp);
	
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
	exit_stat = 1;
	/* exit_stat = printelfh(fp, *argv); */
	return (exit_stat);
}

