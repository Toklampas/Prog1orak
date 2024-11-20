#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct drink {
    char name[32];
    int price;
    struct drink* next;
} drink;
typedef struct pub {
    char name[32];
    drink* price_list;
    struct pub* next;
} pub;

pub* read_pubs(char* name) {
    pub head = {"", NULL, NULL};
    pub** current_pub = &(head.next);
    char buffer[32];
    int price;
    FILE* f = fopen(name, "rt");
    while (fscanf(f, "%31[^\n]\n", buffer) == 1) {
        pub* new_pub = (pub*)malloc(sizeof(pub));
        drink** current_drink;
        strcpy(new_pub->name, buffer);
        new_pub->next = NULL;
        *current_pub = new_pub;
        current_pub = &(new_pub->next);
        new_pub->price_list = NULL;
        current_drink = &(new_pub->price_list);
        while (fscanf(f, "%31[^*.]...%d\n", buffer, &price) == 2) {
            drink* new_drink = (drink*)malloc(sizeof(drink));
            new_drink->price = price;
            strcpy(new_drink->name, buffer);
            new_drink->next = NULL;
            *current_drink = new_drink;
            current_drink = &(new_drink->next);
        }
        fscanf(f, "%*[^\n]\n");
    }
    fclose(f);
    return head.next;
}

pub* find_cheapest(pub *list, char *alc_drink)
{
    if (list == NULL)
        return NULL;
    pub *head = list, *out;
    int min = -1;
    for (pub* current_pub = head; current_pub != NULL; current_pub = current_pub->next)
        for (drink* current_drink = current_pub->price_list; current_drink != NULL; current_drink = current_drink->next)
            if (strcmp(current_drink->name, alc_drink) == 0 && (min == -1 || current_drink->price < min))    
            {
                min = current_drink->price;
                out = current_pub;
            }
    if (min == -1)
        return NULL;
    else
        return out;
}

int main()
{
    //pub* lista = read_pubs("pubs.txt");
    pub* lista = NULL;
    find_cheapest(lista, "bela");
    return 0;
}
