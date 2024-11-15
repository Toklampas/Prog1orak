#include <stdlib.h>

int main()
{
typedef struct _listelem {
    int data;
    struct _listelem* next;
} listelem;

listelem *empty = (listelem*)malloc(sizeof(listelem));
listelem *vege = (listelem*)malloc(sizeof(listelem));

empty->next = vege;
vege->next = NULL;
}
