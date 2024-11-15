#include <stdlib.h>

typedef struct _listelem {
    int a;
    struct _listelem* next;
} listelem;

void reverse_pairs(listelem* head)
{
    listelem* prev = head;
    listelem* first = head->next;
    listelem* second;

    while (first != NULL && first->next != NULL && first->next->next != NULL)
    {
        second = first->next;

        first->next = second->next;
        second->next = first;
        prev->next = second;

        prev = first;
        first = first->next;
    }
    return;
}

//innentol teszteles csak
#include <stdio.h>
listelem* list_from_array(double t[], int n) {
    listelem* last = NULL;
    int i;
    for (i = n - 1; i >= 0; i--) {
        listelem* new = (listelem*)malloc(sizeof(listelem));
        new->a = t[i];
        new->next = last;
        last = new;
    }
    return last;
}

void free_list(listelem* root) {
    while (root != NULL) {
        listelem* next = root->next;
        free(root);
        root = next;
    }
}

int main()
{
    double a[]={0,1,0};
    listelem *c = list_from_array(a, 3);
    reverse_pairs(c);
    return 0;
}