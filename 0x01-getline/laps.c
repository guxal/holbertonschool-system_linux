#include "laps.h"

/**
 * insertsort - inserts linked list in a sorted order
 * @head: pointer to pointer of head node
 * @new: pointer to new node
 */
void insertsort(Nascar **head, Nascar *new)
{
	Nascar **cur;

	cur = head;
	while (*cur && new->id > (*cur)->id)
		cur = &(*cur)->next;
	new->next = *cur;
	*cur = new;
}

/**
 * *add_node - add node in list
 * @head: head
 * @id: id new car
 * Return: Nascar struct
 */
Nascar *add_node(Nascar **head, const int id)
{
	Nascar *new;

	if (head == NULL)
		return (NULL);
	new = malloc(sizeof(Nascar));
	if (new == NULL)
		return (NULL);

	new->id = id;
	new->laps = 0;
	/* new->next = *head; *head = new; */
	insertsort(head, new);
	return (new);
}

/**
 * print_race_state - print race state
 * @head: head node
 */
void print_race_state(Nascar *head)
{
	Nascar *tmp = head;

	printf("Race state:\n");
	while (tmp != NULL)
	{
		printf("Car %d [%lu laps]\n", tmp->id, tmp->laps);
		tmp = tmp->next;
	}
}

/**
 * print_newcar - print new car string
 * @head: head node
 * @i: index new card
 */
void print_newcar(Nascar **head, int i)
{
	add_node(head, i);
	printf("Car %d Joined the race\n", i);
}

/**
 * race_state - race state
 * @id: list of lists the id uniq
 * @size: size lists
 */
void race_state(int *id, size_t size)
{
	size_t i;
	static Nascar *head;
	Nascar *free_tmp;

	if (!size)
	{
		while (head)
		{
			free_tmp = head, head = head->next;
			free(free_tmp);
		} return;
	}
	if (head == NULL)
	{
		for (i = 0; i < size; i++)
			print_newcar(&head, id[i]);
		print_race_state(head);
	} else
	{
		Nascar *tmp = head;
		int exist;

		for (i = 0; i < size; i++)
		{
			exist = 0;
			while (tmp != NULL)
			{
				if (tmp->id == id[i])
					exist = 1, tmp->laps++;
				tmp = tmp->next;
			} tmp = head;
			if (exist == 0)
				print_newcar(&head, id[i]);
		}
		print_race_state(head);
	}
}


