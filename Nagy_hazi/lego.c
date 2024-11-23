/*
Egy szöveges fájl a legósdobozban tárolt alkatrészek katalógusát tartalmazza, minden sora egy alkatrész azonosítóját és darabszámát 
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
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"

//Egy alkatrész adatait tároló struktúra
typedef struct alkatresz_t {
    char id[15]; //Az alkatrész egyedi azonosítója
    unsigned darab; //Az adott alkatrészből hány darab van a dobozban
    struct alkatresz_t *next; //A láncolt lista következő alkatrészére mutató pointer
} alkatresz_t;

//Egy készlet adatait tároló struktúra
typedef struct {
    char nev[150]; //A készlet neve
    alkatresz_t *alkatreszek; //Az alkatrészek listája, amelyekből a készlet áll
    unsigned alkatreszfajta_darab; //Az alkatrészek listájának elemszáma
    unsigned ar; //A készlet ára
} keszlet_t;


//Ez a függvény felszabadítja az alkatrészek listáját
//Bemenetnek az alkatrészek listára mutató pointert kapja meg
void free_alkatresz_lista(alkatresz_t *lista)
{
    alkatresz_t *temp;
    while (lista != NULL)
    {
        temp = lista;
        lista = lista->next;
        free(temp);
    }
}

//Ez a függvény felszabadítja a készletek tömbjét
//Bemenetnek a készletek tömbjére mutató pointert és a készletek számát kapja meg
void free_keszlet_tomb(keszlet_t *keszletek, unsigned keszlet_elemszam)
{
    for (unsigned i = 0; i < keszlet_elemszam; i++)
        free_alkatresz_lista(keszletek[i].alkatreszek);
    free(keszletek);
}

//Ez a függvény beolvassa a dobozban lévő alkatrészeket egy fájlból és visszaadja őket egy láncolt listában
//Bemenetnek a fájl nevét és egy pointert adunk meg, ami a beolvasott alkatrésztípusok számát fogja tárolni
//Viszatérési értéke az alkatrészek listája, ha sikerült beolvasni, egyébként NULL
alkatresz_t* doboz_beolvas(char *fajlnev, unsigned *n)
{
    //Inicializáljuk a változókat
    *n = 0;
    char sor[50];
    alkatresz_t *alkatreszek = NULL;

    //A doboz elemeit tartalmazó fájl megnyitása olvasásra, ha nem sikerül, akkor hibaüzenet és NULL-t ad vissza
    FILE *doboz_fajl = fopen(fajlnev, "r");
    if (doboz_fajl == NULL)
    {
        printf("\nERROR: Nem letezik \"%s\" nevu fajl a mappaban!", fajlnev);
        return NULL;
    }

    //Soronként beolvassuk a fájlt, amíg van mit
    while (fgets(sor, 50, doboz_fajl) != 0)
    {
        //Dinamikusan foglalunk egy új alkatrésznek helyet a memóriában
        //Ha nem sikerül, akkor felszabadítjuk a lista eddigi elemeit, bezárjuk a fájlt és NULL-t adunk vissza
        alkatresz_t *uj_alkatresz = malloc(sizeof(alkatresz_t));
        if (uj_alkatresz == NULL)
        {
            free_alkatresz_lista(alkatreszek);
            fclose(doboz_fajl);
            return NULL;
        }

        //A sorból beolvassuk az alkatrész azonosítóját és darabszámát
        //Ha valami nem stimmel a formátummal, akkor felszabadítjuk az új alkatrészt és NULL-t adunk vissza
        if (sscanf(sor, "%s %d db", uj_alkatresz->id, &uj_alkatresz->darab) == 2)
        {
            uj_alkatresz->next = alkatreszek;
            alkatreszek = uj_alkatresz;
            (*n)++;
        }
        else
        {
            printf("\nERROR: Nem vart formatum a %s fajl %d. soraban: %s", fajlnev, *n + 1, sor);
            free(uj_alkatresz);
            return NULL;
        }
    }

    //Bezárjuk a fájlt és visszaadjuk az alkatrészek listáját
    fclose(doboz_fajl);
    return alkatreszek;
}


//Ez a függvény beolvassa a készleteket egy fájlból és visszaadja őket egy dinamikus tömbben
//Bemenetnek a fájl nevét és egy pointert adunk meg, ami a beolvasott készletek számát fogja tárolni
//Visszatérési értéke a készletek tömbje, ha sikerült beolvasni, egyébként NULL
keszlet_t* keszlet_beolvas(char *fajlnev, unsigned *n)
{
    //Inicializáljuk a változókat
    *n = 0;
    char sor[1000];
    keszlet_t *keszletek = NULL;
    
    //A készletek adatait tartalmazó fájl megnyitása olvasásra, ha nem sikerül, akkor hibaüzenet és NULL-t adunk vissza
    FILE *keszlet_fajl = fopen(fajlnev, "r");
    if (keszlet_fajl == NULL)
    {
        printf("\nERROR: Nem letezik \"%s\" nevu fajl a mappaban!", fajlnev);
        return NULL;
    }

    //Soronként beolvassuk a fájlt, amíg van mit
    while (fgets(sor, 1000, keszlet_fajl) != 0)
    {
        //A készletek tömbjét dinamikusan növeljük, hogy elférjen az új készlet
        //Ha nem sikerül, akkor felszabadítjuk az eddigi készleteket, bezárjuk a fájlt és NULL-t adunk vissza
        keszlet_t *uj_keszletek = realloc(keszletek, (*n + 1) * sizeof(keszlet_t));
        if (uj_keszletek == NULL)
        {
            free(keszletek);
            fclose(keszlet_fajl);
            return NULL;
        }
        else
            keszletek = uj_keszletek;

        //A jelenleg vizsgált készletre mutató pointer létrehozása, majd inicializálása
        keszlet_t *jelenlegi_keszlet = &keszletek[*n];
        jelenlegi_keszlet->alkatreszek = NULL;
        jelenlegi_keszlet->alkatreszfajta_darab = 0;

        //A készlet nevének beolvasása, majd az újsor karakter lecsérése a lezáró nullára
        strncpy(jelenlegi_keszlet->nev, sor, 150);
        *strchr(jelenlegi_keszlet->nev, '\n') = '\0';

        //Az alkatrészek beolvasása, amíg van mit
        if (fgets(sor, 1000, keszlet_fajl) != NULL)
        {
            //Az alkatrészek stringjét szóközöknél elválasztjuk
            char *string_reszlet = strtok(sor, " ");

            while (string_reszlet != NULL)
            {
                //Dinamikusan foglalunk egy új alkatrésznek helyet a memóriában
                //Ha nem sikerül, akkor felszabadítjuk az eddigi alkatrészeket, a készleteket, bezárjuk a fájlt és NULL-t adunk vissza
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

                //Az alkatrész azonosítóját beolvassuk a string részletből
                strncpy(uj_alkatresz->id, string_reszlet, sizeof(uj_alkatresz->id));
                uj_alkatresz->id[sizeof(uj_alkatresz->id) - 1] = '\0';

                //Továbblépünk a következő string részlethez (ami a darabszám)
                string_reszlet = strtok(NULL, " ");

                //Az alkatrész darabszámát beolvassuk a string részletből
                //Ha nem sikerül, akkor felszabadítjuk az új alkatrészt
                if (string_reszlet != NULL && sscanf(string_reszlet, "%d", &uj_alkatresz->darab) == 1)
                {
                    uj_alkatresz->next = jelenlegi_keszlet->alkatreszek;
                    jelenlegi_keszlet->alkatreszek = uj_alkatresz;
                    jelenlegi_keszlet->alkatreszfajta_darab++;
                }
                else
                {
                    printf("\nERROR: Nem vart formatum a %s fajl %d. soraban: %s", fajlnev, *n + 1, sor);
                    free(uj_alkatresz);
                    return NULL;
                }

                //Továbblépünk a következő string részlethez (ami a "db" szó)
                string_reszlet = strtok(NULL, " ");
                //Továbblépünk a következő string részlethez (ami az alkatrész azonosítója)
                string_reszlet = strtok(NULL, " ");
            }
        }
        else break;

        //A készlet árának beolvasása
        if (fgets(sor, 1000, keszlet_fajl) != 0)
            sscanf(sor, "%d", &jelenlegi_keszlet->ar);
        else break;
        //A készletek tömb elemszámának növelése
        (*n)++;
        //Üres sor beolvasása, hogy a következő készlethez léphessünk
        fgets(sor, 1000, keszlet_fajl);

    }

    //Bezárjuk a fájlt és visszaadjuk a készletek tömbjét
    fclose(keszlet_fajl);
    return keszletek;
}

//Ez a függvény megvizsgálja, hogy a megadott készlet kirakható-e a dobozban lévő alkatrészekből
//Bemenetnek a készletet és a dobozban lévő alkatrészeket kapja meg, valamint a dobozban lévő alkatrészek számát és azt, hogy kiírja-e a hiányzó alkatrészeket
//Visszatérési értéke 1, ha a készlet kirakható, 0, ha nem, amennyiben kiírásra kerülnek a hiányzó alkatrészek, akkor 1
int kirakhato_e(keszlet_t *keszlet, alkatresz_t *doboz, unsigned doboz_n, unsigned kiiras) 
{
    //Végigmegyünk az összes alkatrészen a készletben
    int van_hianyzo = 0;
    for (alkatresz_t *jelenlegi_alkatresz = keszlet->alkatreszek; jelenlegi_alkatresz != NULL; jelenlegi_alkatresz = jelenlegi_alkatresz->next)
    {
        int eleg_ez_a_darab = 0;
        //Végigmegyünk az összes alkatrészen a dobozban
        for (alkatresz_t *doboz_alkatresz = doboz; doboz_alkatresz != NULL; doboz_alkatresz = doboz_alkatresz->next)
        {
            //printf("DEBUG: Comparing part %s, needed: %u with part %s, available: %u\n", jelenlegi_alkatresz->id, jelenlegi_alkatresz->darab, doboz_alkatresz->id, doboz_alkatresz->darab);
            //Ha megtaláljuk az alkatrészt a dobozban, akkor megnézzük, hogy elég van-e belőle
            //Ha kiírásra kerülnek a hiányzó alkatrészek, akkor azt is kiírjuk
            if (strcmp(jelenlegi_alkatresz->id, doboz_alkatresz->id) == 0)
            {
                if (doboz_alkatresz->darab >= jelenlegi_alkatresz->darab && kiiras == 0)
                {
                    eleg_ez_a_darab = 1;
                    break;
                }
                else if(kiiras == 1 && doboz_alkatresz->darab < jelenlegi_alkatresz->darab)
                {
                    printf("%s alkatreszbol meg %udb szukseges\n", jelenlegi_alkatresz->id, jelenlegi_alkatresz->darab - doboz_alkatresz->darab);
                    eleg_ez_a_darab = 1;
                    van_hianyzo = 1;
                }
                else if (kiiras == 1 && doboz_alkatresz->darab >= jelenlegi_alkatresz->darab)
                {
                    eleg_ez_a_darab = 1;
                }
            }
        }
        if (!eleg_ez_a_darab && kiiras == 0)
        {
            //printf("DEBUG: Nem található elég %s alkatrész a dobozban\n", jelenlegi_alkatresz->id);
            return 0;
        }
        else if (!eleg_ez_a_darab && kiiras == 1)
        {
            printf("%s alkatreszbol meg %udb szukseges\n", jelenlegi_alkatresz->id, jelenlegi_alkatresz->darab);
            van_hianyzo = 1;
        }
    }
    
    //Ha nincs hiányzó alkatrész és a kiiírás be van kapcsolva, akkor kiírjuk, hogy minden szükséges alkatrész megtalálható
    if (kiiras == 1 && !van_hianyzo)
    {
        printf("Minden szukseges alkatresz megtalalhato a dobozban!\n");
    }

    return 1;
}

//Ez a függvény megkeresi a legdrágább készletet, amely kirakható a dobozban lévő alkatrészekből
//Bemenetnek a készletek tömbjét, a készletek számát, a dobozban lévő alkatrészeket és a dobozban lévő alkatrészek számát kapja meg
//Visszatérési értéke a legdrágább készletre mutató pointer, ha van ilyen, egyébként NULL
keszlet_t* legdragabb_kirakhato_keszlet(keszlet_t *keszletek, unsigned keszletek_n, alkatresz_t *doboz, unsigned doboz_n)
{
    keszlet_t *legdragabb = NULL;
    unsigned max = 0;
    //Végigmegyünk az összes készleten és megnézzük, hogy kirakható-e a dobozban lévő alkatrészekből
    //Ha kirakható és az ára nagyobb, mint a jelenlegi maximum, akkor frissítjük a maximumot és a legdrágább készlet pointerét
    for (unsigned i = 0; i < keszletek_n; i++)
    {
        if (kirakhato_e(&keszletek[i], doboz, doboz_n, 0)) 
        {    
            if (keszletek[i].ar > max)
            {
                max = keszletek[i].ar;
                legdragabb = &keszletek[i];
            }
        }
        //else printf("DEBUG: A %s készlet nem rakható ki a dobozban lévő alkatrészekkel\n", keszletek[i].nev);
    }
    return legdragabb;
}

//Ez a függvény megkeresi a készletet a neve alapján, nem case sensitive módon
//Bemenetnek a készletek tömbjét, a készletek számát és a keresett készlet nevét kapja meg
//Visszatérési értéke a keresett készletre mutató pointer, ha van ilyen, egyébként NULL
keszlet_t* keszlet_keres(keszlet_t *keszletek, unsigned keszletek_n, char *nev)
{
    for (unsigned i = 0; i < keszletek_n; i++)
    {
        //A keresett és a vizsgált készlet nevének összehasonlítása, nagybetűsítve, hogy ne legyen case sensitive a függvény
        char jelenlegi_keszlet_nev[150], keresett_nev[150];
        strcpy(jelenlegi_keszlet_nev, keszletek[i].nev);
        strcpy(keresett_nev, nev);
        if (strstr(strupr(jelenlegi_keszlet_nev), strupr(keresett_nev)) != NULL)
        {
            return &keszletek[i];
        }
    }
    return NULL;
}

//Ez a függvény kiírja a menüt és kezeli a felhasználói bevitelt
//Bemenetnek a készletek tömbjét, a készletek számát, a dobozban lévő alkatrészeket és a dobozban lévő alkatrészek számát kapja meg
//Visszatérési értéke a felhasználó által választott menüpont száma, hiba esetén 0
int menu(keszlet_t *keszletek, unsigned keszlet_elemszam, alkatresz_t *doboz_alkatreszek, unsigned doboz_elemszam)
{
    printf("\n\n\n---------------  Lego kezelo  ---------------");
    printf("\n1. Legdragabb kirakhato keszlet keresese");
    printf("\n2. Keszlet keresese nev szerint");
    printf("\n3. Hianyzo alkatreszek listazasa");
    printf("\n4. Kilepes");
    printf("\n---------------------------------------------");
    printf("\n\nValassz egy muveletet: ");

    int menupont;
    scanf("%d", &menupont);

    switch(menupont)
    {
        case 1:
        {
            keszlet_t *legdragabb_keszlet = legdragabb_kirakhato_keszlet(keszletek, keszlet_elemszam, doboz_alkatreszek, doboz_elemszam);
            if (legdragabb_keszlet != NULL)
                printf("\n\nA legdragabb kirakhato keszlet: %s (ara: %dFt)\n", legdragabb_keszlet->nev, legdragabb_keszlet->ar);
            else
                printf("\n\nEgyik keszlet sem rakhato ki a dobozban levo alkatreszekkel\n");
            return 1;
        }
        case 2:
        {
            char keresett_nev[100];
            printf("\n\nAdd meg a keresett keszlet nevet: ");
            scanf("%99s", keresett_nev);
            keszlet_t *talalt = keszlet_keres(keszletek, keszlet_elemszam, keresett_nev);
            if (talalt)
                printf("\nTalalat: %s - %dFt\n", talalt->nev, talalt->ar);
            else
                printf("\nNem talalhato ilyen nevu keszlet\n");
            return 2;
        }
        case 3:
        {
            char keszlet_nev[100];
            printf("\n\nAdd meg a keszlet nevet: ");
            scanf("%99s", keszlet_nev);
            keszlet_t *keszlet = keszlet_keres(keszletek, keszlet_elemszam, keszlet_nev);
            if (keszlet)
            {
                printf("\nHianyzo alkatreszek a %s keszlet megepitesehez:\n", keszlet->nev);
                kirakhato_e(keszlet, doboz_alkatreszek, doboz_elemszam, 1);
            }
            else
                printf("\nERROR: Nem talalhato ilyen nevu keszlet\n");
            return 3;
        }
        case 4:
        {
            return 4;
        }
        default:
        {
            printf("\nERROR: Nem letezik ilyen menupont\n");
            return 0;
        }
    }
}

//A főprogram
//Bekéri a doboz és a készletek fájl nevét, majd beolvassa őket és meghívja a legdrágább kirakható készletet kereső függvényt
//Ezután kiírja a legdrágább készlet nevét és árát, majd felszabadítja a lefoglalt memóriákat
int main(void)
{
    //A változók inicializálása
    unsigned doboz_elemszam, keszlet_elemszam;
    char doboz_fajlnev[100], keszlet_fajlnev[100];

    //Bekérjük a fájlneveket, limitálva a hosszukat 100 karakterre
    printf("Add meg a doboz fajl nevet (pl. doboz.txt): ");
    scanf("%99s", doboz_fajlnev);
    printf("Add meg a keszletek fajl nevet (pl. keszletek.txt): ");
    scanf("%99s", keszlet_fajlnev);

    //Beolvassuk a fájlokat
    alkatresz_t *doboz_alkatreszek = doboz_beolvas(doboz_fajlnev, &doboz_elemszam);
    if (doboz_alkatreszek == NULL) 
        return 1;

    keszlet_t *keszletek = keszlet_beolvas(keszlet_fajlnev, &keszlet_elemszam);
    if (keszletek == NULL)
    {
        free_alkatresz_lista(doboz_alkatreszek);
        return 1;
    }

    //A menü megjelenítése és a felhasználói bevitel kezelése
    //Addig fut, amíg a felhasználó 4-est nem választ, ekkor véget ér a program
    while (menu(keszletek, keszlet_elemszam, doboz_alkatreszek, doboz_elemszam) != 4);
    
    //Lefoglalt memóriák felszabadítása
    free_keszlet_tomb(keszletek, keszlet_elemszam);
    free_alkatresz_lista(doboz_alkatreszek);

    return 0;
}