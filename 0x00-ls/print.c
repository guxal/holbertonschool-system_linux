#include "hls.h"

/**
 * printInline - print inline
 * @p: path
 * @sp: space
 */
void printInline(char *p, int sp)
{
	if (sp == 0)
		printf("%s", p);
	else if (sp == 1)
		printf(" %s", p);
}


/**
 * print_list_file - print list of file
 * @h: listfile type struct header
 * @options: object with options
 * Return: Count
 */
int print_list_file(const listfile_t *h, option_t *options)
{
	size_t count = 0;
	int sp = 0;

	while (h != NULL)
	{
		if (options->vertical == 1)
			printf("%s\n", h->file);
		else
			printInline(h->file, sp), sp = 1;
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * initPrint - init print spaces
 * @printdata: printdata object
 * @options: object with options
 * Return: None
 */
void initPrint(printdata_t *printdata, option_t *options)
{
	if (printdata->countfile >= 1 && printdata->countdir == 0
		&& options->vertical == 0)
		printf("\n");
	else if (printdata->countfile >= 1 && printdata->countdir >= 1
		&& options->vertical == 0)
		printf("\n\n");
	else if (printdata->countfile >= 1 && printdata->countdir >= 1
		&& options->vertical == 1)
		printf("\n");
}

/**
 * print_list_dir - print list of directories
 * @h: listdir type struct header
 * @printdata: printdata object
 * @options: object with options
 * Return: Count
 */
int print_list_dir(const listdir_t *h, printdata_t *printdata,
					option_t *options)
{
	size_t count = 0;
	read_t *read;
	int sp, nl = 0;

	initPrint(printdata, options);
	while (h)
	{
		if ((printdata->countdir + printdata->countfile) > 1)
			printf("%s:\n", h->path);
		sp = 0, nl = 0;
		while ((read = readdir(h->dir)) != NULL)
		{
			if (read->d_name[0] == '.' && options->hidden == 0)
			{
				if (read->d_name[1] == '.' && read->d_name[2] != 0
					&& options->fullhidden == 1)
				{}
				else if (read->d_name[1] != '.' && read->d_name[1] != 0
					&& options->fullhidden == 1)
				{}
				else
					continue;
			}
			if (options->vertical == 1)
				printf("%s\n", read->d_name);
			else
				printInline(read->d_name, sp), sp = 1;
			nl = 1;
		}
		if (options->vertical == 0 && nl == 1)
			printf("\n");
		if ((printdata->countdir - count) > 1)
			printf("\n");
		h = h->next, count++;
	} return (count);
}
