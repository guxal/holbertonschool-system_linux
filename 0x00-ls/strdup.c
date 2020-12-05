#include "hls.h"

/**
 * _strlen - strlen
 * @str: string
 * Return: integer length
 */
int _strlen(const char *str)
{
	int i = 0;

	while (str[i])
		++i;
	return (i);
}
/**
 * *_strdup - duplicate string
 * @str: string
 * Return: char
 */
char *_strdup(const char *str)
{
	char *new;
	int i = 0;

	if (str == NULL)
		return (NULL);
	new = malloc(sizeof(char) * (_strlen(str) + 1));
	if (new == NULL)
	{
		return (NULL);
	}
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';

	return (new);
}
