#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[15];
    int darab;
} alkatresz_t;

typedef struct {
    char nev[150];
    alkatresz_t alkatreszek[1500];
    int ar;
} keszlet_t;

alkatresz_t* doboz_beolvas(char *fajlnev, int *doboz_elemszam)
{
    *doboz_elemszam = 0;
    char sor[50];
    alkatresz_t *alkatreszek = NULL;

    FILE *doboz_fajl = fopen(fajlnev, "r");
    if (doboz_fajl == NULL)
        return NULL;

    while (fgets(sor, 50, doboz_fajl) != 0)
    {
        alkatresz_t *uj_alkatreszek = realloc(alkatreszek, (*doboz_elemszam + 1) * sizeof(alkatresz_t));
        if (uj_alkatreszek == NULL)
        {
            free(alkatreszek);
            fclose(doboz_fajl);
            return NULL;
        }
        alkatreszek = uj_alkatreszek;
        if (sscanf(sor, "%s %d db", alkatreszek[*doboz_elemszam].id, &alkatreszek[*doboz_elemszam].darab) == 2)
            (*doboz_elemszam)++;
    }
    fclose(doboz_fajl);
    return alkatreszek;
}

keszlet_t* keszlet_beolvas(char *fajlnev, int *keszlet_szam)
{
    *keszlet_szam = 0;
    char sor[1000];
    keszlet_t *keszletek = NULL;
    
    FILE *keszlet_fajl = fopen(fajlnev, "r");
    if (keszlet_fajl == NULL)
        return NULL;

    while (fgets(sor, 1000, keszlet_fajl) != 0)
    {
        keszlet_t *uj_keszletek = realloc(keszletek, (*keszlet_szam + 1) * sizeof(alkatresz_t));
        if (uj_keszletek == NULL)
        {
            free(keszletek);
            fclose(keszlet_fajl);
            return NULL;
        }
        keszletek = uj_keszletek;
    }

    

    fclose(keszlet_fajl);
    return keszletek;
}

int main()
{
    int doboz_elemszam;
    doboz_beolvas("doboz.txt", &doboz_elemszam);
    return 0;
}