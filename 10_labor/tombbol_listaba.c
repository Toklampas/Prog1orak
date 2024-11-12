#include <stdlib.h>

typedef struct list_elem
{
	double data;
	struct list_elem *next;
} list_elem, *list_ptr;

list_ptr array_to_list(double array[], int size)
{
    list_ptr head = NULL;
    for (int i = 0; i < size; i++)
    {    
        list_ptr uj_elem = (list_ptr)malloc(sizeof(list_elem));
        uj_elem->data = array[i];
        uj_elem->next = head;
        head = uj_elem;
    }
    return head;
}