# include "hreadelf.h"


void printshstrndx(Elf64_Half shstrndx64)
{
	printf("%35s%-2c%i\n", "Section header string table index",
			':', shstrndx64);
}

void printshnum(Elf64_Half shnum64)
{
	printf("%27s%-10c%i\n", "Number of section headers", ':',
			shnum64);
}

void printshentsize(Elf64_Half shentsize64)
{
	printf("%25s%-12c%i%s\n", "Size of section headers", ':',
			shentsize64, " (bytes)");
}

void printphnum(Elf64_Half phnum64)
{
	printf("%27s%-10c%i\n", "Number of program headers", ':',
			phnum64);
}

void printhdrsize(Elf64_Ehdr elf64)
{
	Elf64_Half ehsize64 = elf64.e_ehsize;
	Elf64_Half phentsize64 = elf64.e_phentsize;

	printf("%21s%-16c%i%s\n", "Size of this header", ':', ehsize64,
			" (bytes)");
	printf("%25s%-12c%i%s\n", "Size of program headers", ':',
			phentsize64, " (bytes)");
}

void printflags(Elf64_Word flags64)
{
	printf("%7s%-30c0x%x\n", "Flags", ':', flags64);
}

void printpshoff(Elf64_Ehdr elf64)
{
	Elf64_Off phoff64 = elf64.e_phoff;
	Elf64_Off shoff64 = elf64.e_shoff;

	printf("%26s%-11c%li%s\n", "Start of program headers", ':',
			phoff64, " (bytes into file)");
	printf("%26s%-11c%li%s\n", "Start of section headers", ':',
			shoff64, " (bytes into file)");
}

void printentry(Elf64_Addr entry64)
{
	printf("%21s%-16c0x%lx\n", "Entry point address", ':', entry64);
}

void printfileversion(Elf64_Word version)
{
	printf("%9s%-28c%#x\n", "Version", ':',
	version == EV_NONE ? EV_NONE : EV_CURRENT);
}


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
	if (exit_stat)
		return (1);
	exit_stat = printversion(elf64.e_ident, args);
	if (exit_stat)
		return (1);
	/* ------ */
	printosabi(elf64.e_ident);
	printtype(elf64.e_type);
	printmachine(elf64.e_machine);
	printfileversion(elf64.e_version);
	printentry(elf64.e_entry);
	printpshoff(elf64);
	printflags(elf64.e_flags);
	printhdrsize(elf64);
	printphnum(elf64.e_phnum);
	printshentsize(elf64.e_shentsize);
	printshnum(elf64.e_shnum);
	printshstrndx(elf64.e_shstrndx);
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

	exit_stat = printelfh(fp, *argv);
	return (exit_stat);
}

