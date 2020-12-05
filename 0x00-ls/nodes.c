#include "hls.h"

/**
 * add_node_listfile - add node to listfile
 * @head: listfile header
 * @file: name of file
 * Return: Success (listfile_t)
 */
listfile_t *add_node_listfile(listfile_t **head, const char *file)
{
	listfile_t *new;

	if (head == NULL)
		return (NULL);

	new = _salloc(1, sizeof(listfile_t));
	if (new == NULL)
		return (NULL);
	new->file = _strdup(file);
	new->next = *head;
	*head = new;

	return (new);
}

/**
 * add_node_listdir - add node to listdir
 * @head: listdir header
 * @dir: pointer to directory
 * @path: name of path
 * Return: Success (listdir_t)
 */
listdir_t *add_node_listdir(listdir_t **head, DIR *dir, const char *path)
{
	listdir_t *new;

	if (head == NULL)
		return (NULL);

	new = _salloc(1, sizeof(listdir_t));
	if (new == NULL)
		return (NULL);
	new->path = _strdup(path);
	new->dir = dir;
	new->next = *head;
	*head = new;

	return (new);
}

/**
 * buildNodes - build ls nodes
 * @p: path
 * @printdata: struct printdata
 * Return: Success (0), Error (2)
 */
unsigned int buildNodes(char *p, printdata_t *printdata)
{
	DIR *dir;
	struct stat st;

	if (lstat(p, &st) == -1)
		return (ErrorHandler(p));
	if (S_ISREG(st.st_mode))
	{
		/* agrega el file a printdata.listfile */
		add_node_listfile(&printdata->listfile, p), printdata->countfile++;
		return (0);
	}
	dir = opendir(p);/* open dir */
	if (dir == NULL)
		return (ErrorHandler(p));
	/* agrega el readdir(dir) a printdata.listdir y agrega el path */
	add_node_listdir(&printdata->listdir, dir, p), printdata->countdir++;
	return (0);
}
