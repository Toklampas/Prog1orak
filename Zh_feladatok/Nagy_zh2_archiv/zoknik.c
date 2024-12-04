#include <stdlib.h>
#include <string.h>

typedef struct l
{
    int size;
    char color[21];
    struct l *next;
} list_elem, *list_ptr;

void link_back(list_ptr head, list_ptr ujelem) 
{
    while (head->next != NULL)
        head = head->next;
    head->next = ujelem;
    ujelem->next = NULL;
}

int npairs(list_ptr head, list_ptr elem)
{
    int n = 0;
    list_ptr temp = head->next;
    while (temp != NULL)
    {
        if (temp->size == elem->size && strcmp(temp->color, elem->color) == 0)
            n++;
        temp = temp->next;
    }
    return n;
}

void remove_odd(list_ptr head1, list_ptr head2)
{
    list_ptr p = head1;
    list_ptr current = head1->next;
    while (current != NULL)
    {
        if (npairs(head1, current) % 2 == 1)
        {
            p->next = current->next;
            current->next = NULL;
            link_back(head2, current);
            current = p->next;
        }
        else
        {
            p = current;
            current = current->next;
        }
    }
}