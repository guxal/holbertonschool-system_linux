#include "hls.h"

/**
 * ErrorHandler - Handler Error
 * @path: path
 * Return: (Not Return)
 */
void ErrorHandler(char *path)
{
	switch (errno)
	{
	case ENOENT:
		fprintf(stderr, "hls: cannot access %s: No such file or directory\n", path);
		break;
	case EACCES:
		fprintf(stderr, "hls: cannot access %s: Permission denied\n", path);
		break;
	default:
		fprintf(stderr, "hls: cannot access %s: No such file or directory\n", path);
		break;
	}
}

/**
 * printLs - Print Ls Data
 * @dir: directory
 * @path: path
 * @count: count argc
 * @flag: flag for each case
 * Return: (Not Return)
 */
unsigned int printLs(DIR *dir, char *path, int count, int flag)
{
	struct dirent *read;

	if (dir == NULL)
	{
		ErrorHandler(path);
		return (2);
	}
	if (flag != 1)
		printf("%s:\n", path);
	while ((read = readdir(dir)) != NULL)
		if (read->d_name[0] != '.')
			printf("%s ", read->d_name);
	printf("\n");

	if (count != 1)
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
	DIR *dir;

	int saveArgc = argc;
	int result = 0;
	int tmp = 0;

	if (argc > 2)
	{
		while (--argc)
		{
			dir = opendir(argv[argc]);
			tmp = printLs(dir, argv[argc], argc, 0);
			if (tmp != 0)
				result = tmp;
		}
	}

	if (saveArgc <= 2)
	{
		if (saveArgc == 1)
			/* Call the current directory */
			dir = opendir(".");
		else
			dir = opendir(argv[1]);
		result = printLs(dir, argv[1], 1, 1);
	}

	return (result);
}
