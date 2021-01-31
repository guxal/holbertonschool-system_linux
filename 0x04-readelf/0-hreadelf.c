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

void printinstruction(instruction_t instruct[], int size, Elf64_Half match)
{
	int i;
	int m = 0;

	for (i = 0; i < size; i++)
	{
		if (instruct[i].code == match)
		{
			printf("%s\n", instruct[i].str);
			m = 1;
			break;
		}
	}

	if (m != 1)
		printf("%s\n", instruct[0].str);
}

void printmachine(Elf64_Half machine)
{
	instruction_t machines[] = {
	{ EM_NONE, "No machine" },
	{ EM_M32, "AT&T WE 32100" },
	{ EM_SPARC, "Sparc" },
	{ EM_386, "Intel 80386" },
	{ EM_88K, "Motorola m88k family" },
	{ EM_860, "Intel 80860" },
	{ EM_MIPS, "MIPS R3000 big-endian" },
	{ EM_PARISC, "HPPA" },
	{ EM_SPARC32PLUS, "Sun's \"v8plus\"" },
	{ EM_PPC, "PowerPC" },
	{ EM_PPC64, "PowerPC 64-bit" },
	{ EM_S390, "IBM S390" },
	{ EM_ARM, "ARM" },
	{ EM_SH, "Hitachi SH" },
	{ EM_SPARCV9, "SPARC v9 64-bit"},
	{ EM_IA_64, "Intel Merced" },
	{ EM_X86_64, "Advanced Micro Devices X86-64" },
	{ EM_VAX, "Digital VAX" }
	};

	printf("%9s%-28c", "Machine", ':');
	printinstruction(machines, 18, machine);
}

void printtype(Elf64_Half type)
{
	instruction_t types[] = {
	{ ET_NONE, "NONE (No file type)"},
	{ ET_REL, "REL (Relocatable file)" },
	{ ET_EXEC, "EXEC (Executable file)" },
	{ ET_DYN, "DYN (Shared object file)" },
	{ ET_CORE, "CORE (Core file)" }
	};

	printf("%6s%-31c", "Type", ':');
	printinstruction(types, 5, type);
}


void printosabi(char *ident)
{
	instruction_t osabi[] = {
	// { 0, printf("<unknown: %x>\n", ident[EI_OSABI]) },
	{ ELFOSABI_NONE, "UNIX - System V" },
	{ ELFOSABI_HPUX, "UNIX - HP-UX" },
	{ ELFOSABI_NETBSD, "UNIX - NetBSD" },
	{ ELFOSABI_LINUX, "UNIX - Linux" },
	{ ELFOSABI_SOLARIS, "UNIX - Solaris" },
	{ ELFOSABI_IRIX, "UNIX - SGI Irix" },
	{ ELFOSABI_FREEBSD, "UNIX - Compaq TRU64" },
	{ ELFOSABI_ARM, "UNIX - ARM" }
	};
	printf("%8s%-29c", "OS/ABI", ':');
	printinstruction(osabi, 8, ident[EI_OSABI]);
	printf("%14s%24i\n", "ABI Version:", ident[EI_ABIVERSION]);
}


/* ---------------- */


/***/
int printversion(char *ident, char *str)
{
	if (ident[EI_VERSION] == EV_NONE)
	{
		fprintf(stderr, "Error");
		return (1);
	}
	printf("%9s%-28c%i (current)\n", "Version", ':', EV_CURRENT);
	return (0);
}

/***/
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

/***/
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

/***/
void _printmag(char *ident)
{
	size_t i;

	printf("%11s", "Magic:   ");
	for (i = 0; i < EI_NIDENT; ++i)
		printf("%02x ", ident[i]);
	putchar('\n');
}

/* ------------------------------- */

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

