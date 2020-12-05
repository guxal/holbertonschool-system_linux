#include "hls.h"
/**
 * free_listfile - free list file
 * @head: head node list
 */
void free_listfile(listfile_t *head)
{
	listfile_t *tmp;

	tmp = head;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->file);
		free(tmp);
	}
	free(head);
}

/**
 * free_listdir - free list dir
 * @head: head node list
 */
void free_listdir(listdir_t *head)
{
	listdir_t *tmp;

	tmp = head;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->path);
		closedir(tmp->dir);
		free(tmp);
	}
	free(head);
}

/**
 * free_lists - free lists
 * @listdir_head: head node list dir
 * @listfile_head: head node list file
 */
void free_lists(listdir_t *listdir_head, listfile_t *listfile_head)
{
	free_listdir(listdir_head);
	free_listfile(listfile_head);
}
