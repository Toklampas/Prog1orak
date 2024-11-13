#include <stdlib.h>

typedef struct _listelem {
    double data;
    struct _listelem* next;
} listelem;

listelem* merge(listelem* a, listelem* b)
{
    listelem strazsa;
    strazsa.next = NULL;
    listelem *p = &strazsa;

    while(a != NULL && b != NULL)
        if (a -> data < b -> data)
        {
            p->next = a;
            p = p->next;
            a = a->next;
            p->next = NULL;
        }
        else if (b -> data < a -> data)
        {
            p->next = b;
            p = p->next;
            b = b->next;
            p->next = NULL;
        }
    if (a == NULL)
        p->next = b;
    else if (b == NULL)
        p->next = a;
    return strazsa.next;
}



//teszt
listelem* list_from_array(double t[], int n) {
    listelem* last = NULL;
    int i;
    for (i = n - 1; i >= 0; i--) {
        listelem* new = (listelem*)malloc(sizeof(listelem));
        new->data = t[i];
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
    double a[]={1,4,5,7};
    double b[]={2,3,6,8,9,10};
    listelem *c = list_from_array(a, 4);
    listelem *d = list_from_array(b, 6);
    merge(c, d);
    return 0;
}