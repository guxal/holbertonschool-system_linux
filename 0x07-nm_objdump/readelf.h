#ifndef _READELF_H
#define _READELF_H

#include <assert.h>
#include <elf.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <linux/limits.h>
#include <ctype.h>
#include <math.h>


#define GET_BYTE(field) get_byte(field, sizeof(field))
#define ELF_ST_BIND(x) ((x) >> 4)
#define ELF_ST_TYPE(x) (((unsigned int) x) & 0xf)
#define E "Error: Not an ELF file - it has the wrong magic bytes at the start"

/**
 * struct ehdr - Struct to represent headers from both 32 and 64bits files
 * @e_ident : magic number
 * @e_entry : Entry point virtual address
 * @e_phoff : Program header table file offset
 * @e_shoff: Section header table file offset
 * @e_version: Identifies object file version
 * @e_flags: Processor-specific flags
 * @e_type: Identifies object file type
 * @e_machine:  Specifies required architecture
 * @e_ehsize:  ELF header size in bytes
 * @e_phentsize:  Program header table entry size
 * @e_phnum:  Program header table entry count
 * @e_shentsize:  Section header table entry size
 * @e_shnum:  Section header table entry count
 * @e_shstrndx: Section header string table index
 */
typedef struct ehdr
{
	unsigned char e_ident[EI_NIDENT];
	uint64_t e_entry;
	uint64_t e_phoff;
	uint64_t e_shoff;
	uint32_t e_version;
	uint32_t e_flags;
	uint16_t e_type;
	uint16_t e_machine;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;
	uint16_t e_shentsize;
	uint16_t e_shnum;
	uint16_t e_shstrndx;
} ElfN_Ehdr;

/**
 * struct shdr - Struct to represent section headers from both 32 and 64bits
 * @sh_name : offset to a string in the .shstrtab section that represents the
 * name of this section
 * @sh_type : Identifies the type of this header.
 * @sh_flags : Identifies the attributes of the section.
 * @sh_addr: Virtual address of the section in memory, for sections that are
 * loaded.
 * @sh_offset: Offset of the section in the file image.
 * @sh_size: Size in bytes of the section in the file image. May be 0.
 * @sh_link: Contains the section index of an associated section.
 * @sh_info:  Contains extra information about the section.
 * @sh_addralign:  Contains the required alignment of the section.
 * @sh_entsize:  Contains the size, in bytes, of each entry, for sections that
 * contain fixed-size entries
 */
typedef struct shdr
{
	uint32_t sh_name;
	uint32_t sh_type;
	uint64_t sh_flags;
	uint64_t sh_addr;
	uint64_t sh_offset;
	uint64_t sh_size;
	uint32_t sh_link;
	uint32_t sh_info;
	uint64_t sh_addralign;
	uint64_t sh_entsize;
} ElfN_Shdr;

/**
 * struct symtab-  Symbol table entry
 * @st_name : Symbol name, index in string tbl
 * @st_info : Type and binding attributes
 * @st_other :  No defined meaning, 0
 * @st_shndx : Associated section index
 * @st_value : Value of the symbol
 * @st_size : Associated symbol size
 */
typedef struct symtab
{
	uint64_t st_name;
	unsigned char st_info;
	unsigned char st_other;
	uint16_t st_shndx;
	uint64_t st_value;
	uint64_t st_size;
} ElfN_Sym;

/* utils */
uint64_t get_byte_big_endian(uint64_t data, int size);
uint64_t get_byte_host(uint64_t data, int size);
char *read_section(int fd, ElfN_Shdr sh);
char get_st_flag(ElfN_Shdr sh_tbl[], ElfN_Sym symtab, char *strtab);

char determine_st_flag_roftb(ElfN_Sym symtab, char *strtab,
ElfN_Shdr sh_tbl[]);
int is_symbol_from_section(ElfN_Sym symtab, char *strtab,
ElfN_Shdr sb_tbl[], const char *s);

/* 64 */
void read_elf_header_64(ElfN_Ehdr *ehdr, FILE *file);
void read_elf_sh_64(ElfN_Ehdr ehdr, ElfN_Shdr *sh_tbl, int fd);
void read_elf_st_64(ElfN_Ehdr ehdr, ElfN_Shdr shdr, ElfN_Sym *sym_tbl, int fd);

/* 32 */
void read_elf_header_32(ElfN_Ehdr *ehdr, FILE *file);
void read_elf_sh_32(ElfN_Ehdr ehdr, ElfN_Shdr *sh_tbl, int fd);
void read_elf_st_32(ElfN_Ehdr ehdr, ElfN_Shdr shdr, ElfN_Sym *sym_tbl, int fd);


#endif
