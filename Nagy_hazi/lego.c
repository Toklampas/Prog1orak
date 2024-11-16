#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct alkatresz_t {
    char id[15];
    unsigned darab;
    struct alkatresz_t *next;
} alkatresz_t;

typedef struct {
    char nev[150];
    alkatresz_t *alkatreszek;
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
        alkatresz_t *uj_alkatresz = malloc(sizeof(alkatresz_t));
        if (uj_alkatresz == NULL)
        {
            while (alkatreszek != NULL)
            {
                alkatresz_t *temp = alkatreszek;
                alkatreszek = alkatreszek->next;
                free(temp);
            }
            fclose(doboz_fajl);
            return NULL;
        }
        if (sscanf(sor, "%s %d db", uj_alkatresz->id, &uj_alkatresz->darab) == 2)
        {
            uj_alkatresz->next = alkatreszek;
            alkatreszek = uj_alkatresz;
            (*n)++;
        }
        else
        {
            free(uj_alkatresz);
        }
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
            for (int i = 0; i < keszlet_elemszam; i++) {
                alkatresz_t *current = keszletek[i].alkatreszek;
                while (current != NULL) {
                    alkatresz_t *temp = current;
                    current = current->next;
                    free(temp);
                }
            }
            free(keszletek);
            fclose(keszlet_fajl);
            return NULL;
        }
        keszletek = uj_keszletek;
        keszlet_t *jelenlegi_keszlet = &keszletek[*n];
        jelenlegi_keszlet->alkatreszek = NULL;
        jelenlegi_keszlet->alkatreszfajta_darab = 0;

        //nev beolvasasa
        strncpy(jelenlegi_keszlet->nev, sor, 150);
        jelenlegi_keszlet->nev[sizeof(jelenlegi_keszlet->nev) - 1] = '\0';

        //epitoelemek beolvasasa
        if (fgets(sor, 1000, keszlet_fajl) != NULL)
        {
            char *string_reszlet = strtok(sor, " ");
            while (string_reszlet != NULL)
            {
                alkatresz_t *uj_alkatresz = malloc(sizeof(alkatresz_t));
                if (uj_alkatresz == NULL)
                {
                    alkatresz_t *jelenlegi_alkatreszek = jelenlegi_keszlet->alkatreszek;
                    while (jelenlegi_alkatreszek != NULL)
                    {
                        alkatresz_t *temp = jelenlegi_alkatreszek;
                        jelenlegi_alkatreszek = jelenlegi_alkatreszek->next;
                        free(temp);
                    }
                    free(keszletek);
                    fclose(keszlet_fajl);
                    return NULL;
                }

                strncpy(uj_alkatresz->id, string_reszlet, sizeof(uj_alkatresz->id));
                uj_alkatresz->id[sizeof(uj_alkatresz->id) - 1] = '\0';
                string_reszlet = strtok(NULL, " ");
                if (string_reszlet != NULL && sscanf(string_reszlet, "%d", &uj_alkatresz->darab) == 1)
                {
                    uj_alkatresz->next = jelenlegi_keszlet->alkatreszek;
                    jelenlegi_keszlet->alkatreszek = uj_alkatresz;
                    jelenlegi_keszlet->alkatreszfajta_darab++;
                }
                string_reszlet = strtok(NULL, " ");
                string_reszlet = strtok(NULL, " ");
            }
        }
        else break;

        //ar beolvasasa
        if (fgets(sor, 1000, keszlet_fajl) != 0)
            sscanf(sor, "%d", &jelenlegi_keszlet->ar);
        else break;
        (*n)++;
        fgets(sor, 1000, keszlet_fajl);

    }
    fclose(keszlet_fajl);
    return keszletek;
}

int kirakhato_e(keszlet_t *keszlet, alkatresz_t *doboz, unsigned doboz_n)
{
    for (; keszlet->alkatreszek != NULL; keszlet->alkatreszek = keszlet->alkatreszek->next)
    {
        int eleg_ez_a_darab = 0;
        for (int j = 0; j < doboz_n; j++)
            if (strcmp(keszlet->alkatreszek->id, doboz[j].id) == 0)
                if (doboz[j].darab >= keszlet->alkatreszek->darab)
                {
                    eleg_ez_a_darab = 1;
                    break;
                }
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
        alkatresz_t *temp;
        while (doboz_alkatreszek != NULL) {
            temp = doboz_alkatreszek;
            doboz_alkatreszek = doboz_alkatreszek->next;
            free(temp);
        }
        return 1;
    }

    keszlet_t *legdragabb_keszlet = legdragabb_kirakhato_keszlet(keszletek, keszlet_elemszam, doboz_alkatreszek, doboz_elemszam);
    if (legdragabb_keszlet != NULL)
        printf("A legdrágább kirakható készlet: %s", legdragabb_keszlet->nev);
    else
        printf("Egyik készlet sem rakható ki a dobozban lévő alkatrészekkel");
    free(doboz_alkatreszek);
    free(keszletek);
    return 0;
}