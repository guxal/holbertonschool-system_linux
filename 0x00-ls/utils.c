#include "hls.h"


/**
 * sprint_time - returns time string of file
 * @sb: the file in question
 * Return: pointer to time string
 */
char *sprint_time(struct stat sb)
{
	char *p = ctime(&(sb.st_mtime));

	if (_strlen(p) >= 16)
	{
		p += 4;
		p[12] = 0;
	}
	return (p);
}
