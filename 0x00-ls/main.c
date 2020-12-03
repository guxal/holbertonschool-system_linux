#include "hls.h"


/**
 * setOptions - setter options to struct 
 * @option: struct options
 * @param: char params
 * Return: (Not Return)
 */
void setOptions(Option *option, char param)
{
	switch (param)
	{
	case '1':
		/* code */
		option->vertical = 1;
		break;

	case 'a':
		option->hidden = 1;
		break;
	
	default:
		/**error mal parametro */
		perror("parameter invalid");
		exit(2);
		break;
	}
}

/**
 * ErrorHandler - Handler Error
 * @path: path
 * Return: (Not Return)
 */
void ErrorHandler(char *path)
{
	char buf[BUFSIZ];

	if (errno == ENOENT)
		sprintf(buf, "hls: cannot access %s", path);
	else if (errno == EACCES)
		sprintf(buf, "hls: cannot open directory %s", path);
	perror(buf);
}

/**
 * printLs - Print Ls Data
 * @dir: directory
 * @path: path
 * @count: count argc
 * @flag: flag for each case
 * Return: (Not Return)
 */
unsigned int printLs(DIR *dir, char *path, int count, int flag, Option *options)
{
	struct dirent *read;
	// static int call = 1;
	int sp = 0; /* spaces inline */
	int nl = 0; /* new line */

	if (dir == NULL)
	{
		ErrorHandler(path);
		return (2);
	}

	if (flag != 1)
		printf("%s:\n", path);

	while ((read = readdir(dir)) != NULL)
	{
		/* manejo del programa por medio de condicionales */

		if (read->d_name[0] == '.' && options->hidden == 0)  /* leer o no leer hiden files */
			continue;

		/* en linea o con separacion */

		if (options->vertical == 1)
		{
			printf("%s\n", read->d_name);
		} else
		{
			if (sp == 0)
				printf("%s", read->d_name);

			else if (sp == 1)
				printf(" %s", read->d_name);
			sp = 1;
		}
		nl = 1;
	}
	if (options->vertical == 0 && nl == 1)
		printf("\n");

	if (count != 1)
	//if(call >= 2)
		printf("\n");
	
	//printf("count %d\n", count);
	closedir(dir);
	// printf("call: %d\n", call);
	//++call;
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
	DIR *dir;

	int saveArgc = argc;
	int result = 0;
	int tmp = 0;
	int flag = 0;
	int runtime = 0;
	// char *path = ".";
	Option options = OPTION_INIT;

	/** while options */
	int inc = 1;
	while (inc != argc)
	{

		if (argv[inc][0] == '-' && argv[inc][1] != 0)
		//if (**argv == '-' && *(*args + 1))
		{
			// printf("param: %c\n", argv[inc][0]);
			/* añadir configuracion */
			setOptions(&options, argv[inc][1]);
			inc++;
			runtime = 1;
		} else {
			break;
		}
	}
	// printf("argc: %d", argc);
	/** while paths */
	flag = (argc - inc) == 1;
	//printf("rest: %d\n", (argc - inc));
	//printf("flag: %d\n", flag);

	while (inc != argc)
	{
		dir = opendir(argv[inc]);
		tmp = printLs(dir, argv[inc], (argc - inc), flag, &options);
		if (tmp != 0)
			result = tmp;
		inc++;
		runtime = 2;
	}
	// if not pass paths 
	//printf("runtime : %d\n", runtime);
	// and if pass options and not paths
	if (argc == 1 && (inc - argc) == 0 || runtime < 2)
	{
		dir = opendir(".");
		result = printLs(dir, argv[1], 1, 1, &options);
	}

	return (result);
}
