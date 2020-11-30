#include "hls.h"

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	struct dirent *read;
	DIR *dir;

	dir = opendir(".");

	while ((read = readdir(dir)) != NULL)
		if (read->d_name[0] != '.')
			printf("%s ", read->d_name);
	printf("\n");

	closedir(dir);

	return (0);
}
