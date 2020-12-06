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
		printf("  %s", p);
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
		if (options->vertical == 1 && options->fulldata == 0)
			printf("%s\n", h->file);
		else if (options->vertical >= 0 && options->fulldata == 1)
			printLongListing(h->sb, h->file, h->file);
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
		&& options->vertical == 0 && options->fulldata == 0)
		printf("\n");
	else if (printdata->countfile >= 1 && printdata->countdir >= 1
		&& options->vertical == 0)
		printf("\n\n");
	else if (printdata->countfile >= 1 && printdata->countdir >= 1
		&& options->vertical == 1 && options->fulldata == 1)
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
	struct stat st;
	int sp, nl = 0;

	initPrint(printdata, options);
	while (h)
	{
		if ((printdata->countdir + printdata->countfile + printdata->result) > 1)
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
			if (options->vertical == 1 && options->fulldata == 0)
				printf("%s\n", read->d_name);
			else if (options->vertical >= 0 && options->fulldata == 1)
				lstat(read->d_name, &st), printLongListing(st, read->d_name, h->path);
			else
				printInline(read->d_name, sp), sp = 1;
			nl = 1;
		}
		if (options->vertical == 0 && nl == 1 && options->fulldata == 0)
			printf("\n");
		if ((printdata->countdir - count) > 1)
			printf("\n");
		h = h->next, count++;
	} return (count);
}

/**
 * printLongListing - print using a long listing format
 * @sb: struct
 * @name: name of file
 * @p: path
 */
void printLongListing(struct stat sb, char *name, char *p)
{
	struct passwd *usr = getpwuid(sb.st_uid);
	struct group *grp = getgrgid(sb.st_gid);

	printf("%c%c%c%c%c%c%c%c%c%c %-*lu ",
		S_ISDIR(sb.st_mode) ? 'd' : S_ISLNK(sb.st_mode) ? 'l' : '-',
		RUSR, WUSR, XUSR, RGRP, WGRP, XGRP, ROTH, WOTH, XOTH,
		0, sb.st_nlink);

	if (usr)
		printf("%-*s ", 0, usr->pw_name);
	else
		printf("%*u ", 0, sb.st_uid);

	if (grp)
		printf("%-*s ", 1, grp->gr_name);
	else
		printf("%*u ", 1, sb.st_gid);

	printf("%*lu %s %s", 0,
		sb.st_size, sprint_time(sb), name);
	if (S_ISLNK(sb.st_mode))
	{
		char buf[256] = {0};

		readlink(p, buf, 256);
		printf(" -> %s", buf);
	}
	printf("\n");
}
