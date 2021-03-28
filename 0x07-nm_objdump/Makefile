CC 		= gcc-4.8
CFLAGS 	= -Wall -Werror -Wextra -pedantic -g

_SRC 	= nm.c \
		  elf_utils.c \
		  elf_utils_1.c \
		  elf_print.c \
		  elf_functions_32.c \
		  elf_functions_64.c \
		  elf_symbols_tables.c

SRC 	= $(patsubst %,%,$(_SRC))

_OBJ	= $(_SRC:.c=.o)
OBJECTS = $(patsubst %,%,$(_OBJ))

IDIR	= .
SDIR	= .
ODIR	= .

OUTPUT	= hnm

%.o : %.c
		$(CC) $(CFLAGS) -c -o $@ $< -I$(IDIR)

all : $(OUTPUT)

$(OUTPUT) : $(OBJECTS)
		$(CC) -o $@ $^ $(LINKS)

.PHONY : clean

clean :
	rm *.o

re: $(OBJ)
