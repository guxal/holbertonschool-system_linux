#include "laps.h"
/*
 * Appends a single element at the head of the list
 * List is passed by address, so the content of the caller
 * variable is updated to point to the new head
 *
 * Complexity: O( 1 )
*/
void list_add_node( Nascar **list, Nascar *node )
{
    node->next = *list;
    *list = node;
}
 
/*
 * Append list at the end of another list
 * Head list is passed by address, so the content of the caller
 * variable can be updated to poin to the new head
 * if the original list was empty (NULL)
 *
 * Complexity: O( len(l0) )
 */
void list_concat( Nascar **l0, Nascar *l1 )
{
    /* We find the address of the pointer that needs to be updated */
    while (*l0)
        l0 = &((*l0)->next);
   
    /* We update it to point to the new tail */
    *l0 = l1;
}
 
/*
 * Quick sort of the list
 * This is a naive quicksort implementation:
 * a) It will decay into n^2 complexity if the list is already sorted
 * b) It scans the list multiple time to concatenate
 *    (this can easily be avoided by keeping track of the address of the end of left)
 *
 * Complexity:
 *   best     : O( len(list) )
 *   average  : O( len(list)*log(len(list)) )
 *   worst    : O( len(list)^2 )
 */
void my_qsort( Nascar **list )
{
    /* Sorting an empty list is trivial */
    if (!*list)
        return;
 
    /* Extract the pivot */    
    Nascar *pivot = *list;
    int data = pivot->id;
    Nascar *p = pivot->next;
    pivot->next = NULL;
 
    /* Construct left and right lists in place in a single pass*/
    Nascar *left = NULL;
    Nascar *right = NULL;
 
    while (p)
    {
        Nascar *n = p;  
        p = p->next;
        if (n->id<data)
            list_add_node( &left, n );
        else
            list_add_node( &right, n );
    }
 
    /* We now sort left and right */
    /* If left and right are of vastly different lengths, the complexity won't be O(n log n) */
    my_qsort( &left );
    my_qsort( &right );
 
    /* We now concatenate lists [this is inefficient, but doesn't hurt complexity] */
    Nascar *result = NULL;
    list_concat( &result, left );
    list_concat( &result, pivot );
    list_concat( &result, right );
    *list = result;
}

/**
 * _strlen - strlen
 * @str: string
 * Return: string
 */

int _strlen(const char *str)
{
	int count = 0;

	while (str[count])
		++count;
	return (count);
}
/**
 * *add_node - add node in list
 * @head: head
 * @str: string
 * Return: List_t
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
	new->next = *head;
	*head = new;

	return (new);
}

void print_race_state(Nascar *idn)
{
    printf("Race state:\n");
    Nascar *tmp = idn;

    while(tmp != NULL)
    {
        printf("Car %d [%zu laps]\n", tmp->id, tmp->laps);
        tmp = tmp->next;
    }
}

void race_state(int *id, size_t size)
{
    //static int **ids = NULL;
    static Nascar *idn = NULL;
    //(void) *ids;
    //(void) size;
    Nascar *free_tmp;
    if (!size)
	{
		while (idn)
		{
			free_tmp = idn;
			idn = idn->next;
			free(free_tmp);
		}
		return;
	}

    if (idn == NULL){
        //ids = (int**) malloc(sizeof(int*) * size + 1);
        //memset(ids, 0x0, sizeof(int*) * size + 1);
        //idn = malloc(sizeof(Nascar));
        //if (ids == NULL)
		//    return;
        //printf("%x", ids);
        //printf("%d", *ids);
        //printf("%d", **ids);

        for (size_t i = 0; i < size; i++)
        {

            //printf("%i\n", id[i]);
            add_node(&idn, id[i]);
            //ids[i] = (int*) malloc(sizeof(int) * 2);
            //memset(ids[i], 0x00, sizeof(int) * 2);
        //    /* code */
            //ids[i][0] = id[i];
            //ids[i][1] = 0;
////
            printf("Car %d Joined the race\n", id[i]);
        }

        my_qsort(&idn);
        //ids[i] = NULL;
        // printf("%d\n", ids[0][0]);
        // printf("%d\n", ids[1][0]);
        // printf("%d\n", ids[2][0]);
        print_race_state(idn);
    } else {

        //int count = 0;
        Nascar *tmp = idn;
        Nascar *tmp2 = idn;
        while(tmp != NULL)
        {
            for (size_t i = 0; i < size; i++)
            {
                if (tmp->id == id[i])
                {
                    tmp->laps++;
                }
            }
        //    count++;
            tmp = tmp->next;
        }

        int exist;
        //int count2;
        for(size_t i = 0; i < size; i++)
        {
            exist = 0;
        //    count2 = 0;
            while(tmp2 != NULL)
            {
                if (tmp2->id == id[i])
                {
                    exist = 1;
                }
                tmp2 = tmp2->next;
            }

            tmp2 = idn;

            if (exist == 0)
            {
                //printf("dont exists\n");
                add_node(&idn, id[i]);
                printf("Car %d Joined the race\n", id[i]);
            }
        }
        my_qsort(&idn);
        print_race_state(idn);

    }
    /* while(*id){
       printf("%i\n", *id);
       id++;
    } */
}


