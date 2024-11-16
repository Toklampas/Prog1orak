/*
Egy szöveges fájl a legósdobozban tárolt alkatrészek katalógusát tartalmazza, minden sora egy 
alkatrész azonosítóját és darabszámát 
Példa: 
4515374/60481 6 db 
4515323/60412 10 db 
4530042/60117 5 db 
4523109/60589 15 db 
4537118/60600 7 db 
4529082/60533 20 db 
Egy másik szöveges fájl lego készleteket tárol, minden készletet három sorban, az alábbi 
szerkezet szerint. A készleteket egymástól egy üres sor választja el. 
1. sor: készlet neve: pl. NASA Apollo 11 holdkomp 
2. sor: készlet építőelemei: pl. 4515374/60481 6 db 4515323/60412 3 db ... stb. 
3. sor: készlet ára pl. 25000 
A program kiírja, hogy melyik az a legdrágább készlet, mely a legósdobozban tárolt elemekből 
kirakható.


A kitűzött feladattal kapcsolatban az alábbiakat várjuk el:

Kell, hogy szerepeljen benne szöveges fájlkezelés
Kell, hogy szerepeljen benne dinamikus adatszerkezet
Kell, hogy szerepeljen benne sztringfeldolgozás
Az elvárásoknak tipikusan jól megfelelnek olyan jellegű feladatok, melyek
szöveges fájlokból adatokat olvasnak be
azokat dinamikus adatszerkezetben tárolják
majd egy adott kérdés megválaszolásához a tárolt adatsorokat többször be kell járniuk.

A fájlokat csak egyszer olvashatja végig a program beolvasó rutinja,
Az adatok feldolgozása szekvenciálisan történjen,
A fájlok méretét nem szabad az operációs rendszer segítségével lekérdezni és felhasználni,
A feldolgozandó adatok egy részét vagy egészét, az adatok közti kapcsolatoknak megfelelően egy összetettebb dinamikus adatszerkezetben, a memóriában kell tárolni (a dinamikusan nyújtózkodó tömböt nem fogadjuk el dinamikus adatszerkezetként)
Az adatszerkezetben ne legyenek többszörösen tárolt adatok
A dinamikus adatszerkezetet úgy kell megtervezni, hogy azon a végeredmény kiszámításhoz használt algoritmus hatékonyan működjön (vagyis a teljesen általános, mindent egyetlen univerzális adattípusban tároló megoldás nem elfogadott),
Törekedni kell a program megfelelő szintű dekompozíciójára (függvényekre bontás)
A programban figyelni kell a memóriagazdálkodásra (ne szivárogjon a memória)
A programnak nem csak egyetlen adatsoron kell jól működnie
A teszteléshez természetesen nem kell valóságos adatsorokat felhasználni, hanem olyan tesztadatokat találjunk ki és használjunk, amiken megmutatható, hogy nem csak a kézenfekvő esetekben működik helyesen a program
A tesztadatokat tartalmazó fájlok elkészítése is része a feladatnak.
*/

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
            free(keszletek);
            fclose(keszlet_fajl);
            return NULL;
        }
        keszletek = uj_keszletek;
        keszlet_t *jelenlegi_keszlet = &keszletek[*n];
        jelenlegi_keszlet->alkatreszek = NULL;
        jelenlegi_keszlet->alkatreszfajta_darab = 0;

        //nev beolvasasa, sor atmasolasa a nevbe
        strncpy(jelenlegi_keszlet->nev, sor, 150);
        //a nev str vegi uj sor karakter atalakitasa lezaro nullara
        *strchr(jelenlegi_keszlet->nev, '\n') = '\0';

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
    for (alkatresz_t *jelenlegi_alkatresz = keszlet->alkatreszek; jelenlegi_alkatresz != NULL; jelenlegi_alkatresz = jelenlegi_alkatresz->next)
    {
        int eleg_ez_a_darab = 0;
        for (alkatresz_t *doboz_alkatresz = doboz; doboz_alkatresz != NULL; doboz_alkatresz = doboz_alkatresz->next)
        {
            //printf("DEBUG: Comparing part %s, needed: %u with part %s, available: %u\n", jelenlegi_alkatresz->id, jelenlegi_alkatresz->darab, doboz_alkatresz->id, doboz_alkatresz->darab);
            if (strcmp(jelenlegi_alkatresz->id, doboz_alkatresz->id) == 0)
            {
                if (doboz_alkatresz->darab >= jelenlegi_alkatresz->darab)
                {
                    eleg_ez_a_darab = 1;
                    break;
                }
            }
        }
        if (!eleg_ez_a_darab)
        {
            //printf("DEBUG: Nem található elég %s alkatrész a dobozban\n", jelenlegi_alkatresz->id);
            return 0;
        }
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
        else
            //printf("DEBUG: A %s készlet nem rakható ki a dobozban lévő alkatrészekkel\n", keszletek[i].nev);
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