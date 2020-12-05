#include "hls.h"

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
