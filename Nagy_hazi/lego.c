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
    int alkatreszfajta_darab;
    int ar;
} keszlet_t;

alkatresz_t* doboz_beolvas(char *fajlnev, int *n)
{
    *n = 0;
    char sor[50];
    alkatresz_t *alkatreszek = NULL;

    FILE *doboz_fajl = fopen(fajlnev, "r");
    if (doboz_fajl == NULL)
        return NULL;

    while (fgets(sor, 50, doboz_fajl) != 0)
    {
        alkatresz_t *uj_alkatreszek = realloc(alkatreszek, (*n + 1) * sizeof(alkatresz_t));
        if (uj_alkatreszek == NULL)
        {
            free(alkatreszek);
            fclose(doboz_fajl);
            return NULL;
        }
        alkatreszek = uj_alkatreszek;
        if (sscanf(sor, "%s %d db", alkatreszek[*n].id, &alkatreszek[*n].darab) == 2)
            (*n)++;
    }
    fclose(doboz_fajl);
    return alkatreszek;
}

keszlet_t* keszlet_beolvas(char *fajlnev, int *n)
{
    *n = 0;
    int i = 0;
    char sor[1000], nev[150];
    keszlet_t *keszletek = NULL;
    
    FILE *keszlet_fajl = fopen(fajlnev, "r");
    if (keszlet_fajl == NULL)
        return NULL;

    while (fgets(sor, 1000, keszlet_fajl) != 0)
    {
        keszlet_t *uj_keszletek = realloc(keszletek, (*n + 1) * sizeof(keszlet_t));
        if (uj_keszletek == NULL)
        {
            free(keszletek);
            fclose(keszlet_fajl);
            return NULL;
        }
        keszletek = uj_keszletek;

        //nev beolvasasa
        strncpy(keszletek[*n].nev, sor, 150);
        keszletek[*n].nev[sizeof(keszletek[*n].nev) - 1] = '\0';

        //epitoelemek beolvasasa
        keszlet_t *k = &keszletek[*n];
        if (fgets(sor, 1000, keszlet_fajl) != 0)
        {
            keszletek[*n].alkatreszfajta_darab = 0;
            char *alkatresz = strtok(sor, " ");
            while (alkatresz != NULL && keszletek[*n].alkatreszfajta_darab < 1500)
            {
                
            }
        }
        else break;

        //ar beolvasasa
        if (fgets(sor, 1000, keszlet_fajl) != 0)
            sscanf(sor, "%d", keszletek[*n].ar);
        else break;
        (*n)++;

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