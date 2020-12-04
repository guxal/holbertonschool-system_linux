#include "hls.h"


/**
 * setOptions - setter options to struct
 * @option: struct options
 * @param: char params
 * Return: (Not Return)
 */
void setOptions(Option *option, char *param)
{
	while (*++param)
	{
		switch (*param)
		{
			case '1':
				/* code */
				option->vertical = 1;
				break;

			case 'a':
				option->hidden = 1;
				break;

			case 'A':
				option->fullhidden = 1;
				break;

			default:
				/**error mal parametro */
				fprintf(stderr, "hls: invalid option -- '%c'\n", *param);
				fprintf(stderr, "Try '%s --help' for more information.\n", "ls");
				exit(2);
				break;
		}
	}
}

/**
 * ErrorHandler - Handler Error
 * @path: path
 * Return: 2
 */
unsigned int ErrorHandler(char *path)
{
	char buf[BUFSIZ];

	if (errno == ENOENT)
		sprintf(buf, "hls: cannot access %s", path);
	else if (errno == EACCES)
		sprintf(buf, "hls: cannot open directory %s", path);
	perror(buf);
	return (2);
}

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
 * printLs - Print Ls Data
 * @p: path for errors and output
 * @c: count paths argc desc
 * @f: flag for each case
 * @options: object with options
 * Return: 0 Success or 2 Error
 */
unsigned int printLs(char *p, int c, int f, Option *options)
{
	struct dirent *read;
	int sp = 0, nl = 0;
	DIR *dir;
	struct stat st;

	if (lstat(p, &st) == -1)
		return (ErrorHandler(p));
	if (S_ISREG(st.st_mode))
	{
		printf("%s\n", p);
		return (0);
	}
	dir = opendir(p);/* open path */
	if (dir == NULL)
		return (ErrorHandler(p));
	if (f != 1)
		printf("%s:\n", p);
	while ((read = readdir(dir)) != NULL)
	{
		if (read->d_name[0] == '.' && options->hidden == 0)
		{
			if (read->d_name[1] != '.' && read->d_name[1] != 0
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
	if (c != 1)
		printf("\n");
	closedir(dir);
	return (0);
}

/**
 * main - Entry point
 * @argc: count arg
 * @argv: array arg
 * Return: Always 0 (Success)
 */
int main(int argc, char *argv[])
{
	int result = 0;
	int tmp = 0;
	int flag = 0;
	int runtime = 0;
	Option options = OPTION_INIT;
	/** while options */
	int inc = 1;
	int inc2 = 1;
	int numberpaths = 1;

	while (inc != argc)
	{
		if (argv[inc][0] == '-' && argv[inc][1] != 0)
		{
			setOptions(&options, argv[inc]);
			runtime = 1;
			inc2++;
		} inc++;
	}
	/** if more two paths is 0 else 1 */
	flag = (argc - inc2) == 1, numberpaths = (argc - inc2) + 1;
	/** while paths */
	inc = 1, inc2 = 1;
	while (inc != argc)
	{
		if (argv[inc][0] == '-' && argv[inc][1] != 0)
		{
			inc++;
			continue;
		}
		tmp = printLs(argv[inc], (numberpaths - inc2), flag, &options);
		if (tmp != 0)
			result = tmp;
		inc++, runtime = 2, inc2++;
	}
	/* if not pass paths and if pass options and not paths */
	if ((argc == 1 && (inc - argc) == 0) || runtime < 2)
		result = printLs(".", 1, 1, &options);
	return (result);
}
