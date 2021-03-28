CC 		= gcc-4.8
CFLAGS 	= -Wall -Werror -Wextra -pedantic -g

_SRC 	= nm.c \
		= elf_utils.c \
		= elf_utils_1.c \
		= elf_print.c \
		= elf_functions_32.c \
		= elf_functions_64.c \
		= elf_symbols_tables.c

SRC 	= $(patsubst %,$(SDIR)/%,$(_SRC))

_OBJ	= $(_SRC:.c=.o)
OBJECTS = $(patsubst %,$(ODIR)/%,$(_OBJ))

IDIR	= .
SDIR	= .
ODIR	= .

OUTPUT	= hnm

$(ODIR)/%.o : $(SDIR)/%.c
		$(CC) $(CFLAGS) -c -o $@ $< -I$(IDIR)

all : $(OUTPUT)

$(OUTPUT) : $(OBJECTS)
		$(CC) -o $@ $^ $(LINKS)

.PHONY : clean

clean :
	rm -f $(OUTPUT) $(OBJECTS)

re: $(OBJ)
