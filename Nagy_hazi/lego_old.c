#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[15];
    unsigned darab;
} alkatresz_t;

typedef struct {
    char nev[150];
    alkatresz_t alkatreszek[1500];
    unsigned alkatreszfajta_darab;
    unsigned ar;
} keszlet_t;

alkatresz_t* doboz_beolvas(char *fajlnev, unsigned *n)
{
    *n = 0;
    char sor[50];
    alkatresz_t *alkatreszek = NULL;

    FILE *doboz_fajl = fopen(fajlnev, "r");
    if (doboz_fajl == NULL)
    {
        printf("ERROR: Nem létezik %s nevű fájl a mappában!", fajlnev);
        return NULL;
    }

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

keszlet_t* keszlet_beolvas(char *fajlnev, unsigned *n)
{
    *n = 0;
    int i = 0;
    char sor[1000], nev[150];
    keszlet_t *keszletek = NULL;
    
    FILE *keszlet_fajl = fopen(fajlnev, "r");
    if (keszlet_fajl == NULL)
    {
        printf("ERROR: Nem létezik %s nevű fájl a mappában!", fajlnev);
        return NULL;
    }

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
            char *string_reszlet = strtok(sor, " ");
            while (string_reszlet != NULL && keszletek[*n].alkatreszfajta_darab < 1500)
            {
                strncpy(keszletek[*n].alkatreszek[keszletek[*n].alkatreszfajta_darab].id, string_reszlet, sizeof(keszletek[*n].alkatreszek[keszletek[*n].alkatreszfajta_darab].id));
                keszletek[*n].alkatreszek[keszletek[*n].alkatreszfajta_darab].id[sizeof(keszletek[*n].alkatreszek[keszletek[*n].alkatreszfajta_darab].id)-1] = '\0';
                string_reszlet = strtok(NULL, " ");
                if (string_reszlet != NULL && sscanf(string_reszlet, "%d", &keszletek[*n].alkatreszek[keszletek[*n].alkatreszfajta_darab].darab) == 1)
                    keszletek[*n].alkatreszfajta_darab++;
                string_reszlet = strtok(NULL, " ");
                string_reszlet = strtok(NULL, " ");
            }
        }
        else break;

        //ar beolvasasa
        if (fgets(sor, 1000, keszlet_fajl) != 0)
            sscanf(sor, "%d", &keszletek[*n].ar);
        else break;
        (*n)++;
        fgets(sor, 1000, keszlet_fajl);

    }
    fclose(keszlet_fajl);
    return keszletek;
}

int kirakhato_e(keszlet_t *keszlet, alkatresz_t *doboz, unsigned doboz_n)
{
    int eleg_ez_a_darab = 0;
    for (int i = 0; i < (*keszlet).alkatreszfajta_darab; i++)
    {
        for (int j = 0; j < doboz_n; j++)
            if (strcmp((*keszlet).alkatreszek[i].id, doboz[j].id) == 0)
                if (doboz[j].darab >= (*keszlet).alkatreszek[i].darab)
                    eleg_ez_a_darab = 1;
        if (!eleg_ez_a_darab)
            return 0;
    }
    return 1;
}

keszlet_t* legdragabb_kirakhato_keszlet(keszlet_t *keszletek, unsigned keszletek_n, alkatresz_t *doboz, unsigned doboz_n)
{
    keszlet_t *legdragabb = NULL;
    int max = 0;
    for (int i = 0; i < keszletek_n; i++)
        if (kirakhato_e(&keszletek[i], doboz, doboz_n)) 
            if (keszletek[i].ar > max)
            {
                max = keszletek[i].ar;
                legdragabb = &keszletek[i];
            }
    return legdragabb;
}

int main()
{
    unsigned doboz_elemszam;
    unsigned keszlet_elemszam;

    alkatresz_t *doboz_alkatreszek = doboz_beolvas("doboz.txt", &doboz_elemszam);
    if (doboz_alkatreszek == NULL) 
        return 1;

    keszlet_t *keszletek = keszlet_beolvas("keszletek.txt", &keszlet_elemszam);
    if (keszletek == NULL)
    {
        free(doboz_alkatreszek);
        return 1;
    }

    keszlet_t *legdragabb_keszlet = legdragabb_kirakhato_keszlet(keszletek, keszlet_elemszam, doboz_alkatreszek, doboz_elemszam);
    if (legdragabb_keszlet != NULL)
        printf("A legdrágább kirakható készlet: %s", (*legdragabb_keszlet).nev);
    else
        printf("Egyik készlet sem rakható ki a dobozban lévő alkatrészekkel");
    free(doboz_alkatreszek);
    free(keszletek);
    return 0;
}