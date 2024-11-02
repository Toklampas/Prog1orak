#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[15];
    int darab;
} alkatresz;

typedef struct {
    char nev[150];
    alkatresz *alkatreszek;
    int ar;
} keszlet;

int doboz_beolvas(alkatresz *elemek, char *fajlnev)
{
    FILE *doboz_fajl = fopen(fajlnev, "r");
    if (doboz_fajl == NULL)
        return -1;
    int i = 0;
    while (fscanf(doboz_fajl, "%s%ddb", elemek[i].id, &elemek[i].darab) == 2)
        i++;
    fclose(doboz_fajl);
    return i;
}

int keszlet_beolvas(keszlet *keszletek, char *fajlnev)
{
    FILE *keszlet_fajl = fopen(fajlnev, "r");
    if (keszlet_fajl == NULL)
        return -1;
    
}