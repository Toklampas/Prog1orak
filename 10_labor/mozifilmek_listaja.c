#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char title[20];
    double popularity; // 1..5
} movie;

typedef struct l {
    movie m;
    struct l* next;
} listelem;

void print_movies(listelem *head)
{
    listelem *elem = head->next;
    while (elem->next != NULL)
    {
        printf("%-19s (", elem->m.title);
        int n = (int)round(elem->m.popularity);
        for (int i = 0; i < 5; i++)
        {
            if (i < n)
                printf("*");
            else
                printf(" ");
        }
        printf(")\n");
        elem = elem->next;
    }
}

void insert_movie(listelem *head, char *title, double popularity)
{
    listelem *new_movie = (listelem *)malloc(sizeof(listelem));
    strcpy(new_movie->m.title, title);
    new_movie->m.popularity = popularity;
    new_movie->next = NULL;

    listelem *elem = head;
    while (elem->next != NULL && elem->next->m.popularity > popularity)
        elem = elem -> next;
    new_movie->next = elem->next;
    elem->next = new_movie;
}



//teszteles
int main() {
    listelem *head = (listelem *)malloc(sizeof(listelem));
    head->next = NULL;

    insert_movie(head, "The Godfather", 4.7);
    insert_movie(head, "ASDSADASD", 3);
    insert_movie(head, "Strázsa úgyse számít", 1);

    print_movies(head);

    listelem *current = head;
    while (current != NULL)
    {
        listelem *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}