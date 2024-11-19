#include <stdio.h>
#include <stdlib.h>

typedef struct _point_listelem {
    double x, y, z;
    struct _point_listelem* next;
} point_listelem;

void save(char *filename, point_listelem *head)
{
    FILE *f = fopen(filename, "wb");
    if (f == NULL)
        return;

    while (head != NULL)
    {
        fwrite(&(head->x), sizeof(double), 1, f);
        fwrite(&(head->y), sizeof(double), 1, f);
        fwrite(&(head->z), sizeof(double), 1, f);
        head = head->next;
    }

    fclose(f);
}

point_listelem* restore(char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (f == NULL)
        return NULL;

    point_listelem* head = NULL;
    point_listelem* tail = NULL;
    double x, y, z;
    
    while (fread(&x, sizeof(double), 1, f) == 1 && fread(&y, sizeof(double), 1, f) == 1 && fread(&z, sizeof(double), 1, f) == 1)
    {
        point_listelem* new_elem = malloc(sizeof(point_listelem));
        if (new_elem == NULL)
        {
            fclose(f);
            return NULL;
        }

        new_elem->x = x;
        new_elem->y = y;
        new_elem->z = z;
        new_elem->next = NULL;

        if (head == NULL)
        {
            head = new_elem;
            tail = new_elem;
        } 
        else
        {
            tail->next = new_elem;
            tail = new_elem;
        }
    }

    fclose(f);
    return head;
}
