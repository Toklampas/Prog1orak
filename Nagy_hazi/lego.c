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
        printf("\nERROR: Nem létezik \"%s\" nevű fájl a mappában!", fajlnev);
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
            while (alkatreszek != NULL)
            {
                alkatresz_t *temp = alkatreszek;
                alkatreszek = alkatreszek->next;
                free(temp);
            }
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
            printf("\nERROR: Nem várt formátum a %s fájl %d. sorában: %s", fajlnev, *n + 1, sor);
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
    int i = 0;
    char sor[1000], nev[150];
    keszlet_t *keszletek = NULL;
    
    //A készletek adatait tartalmazó fájl megnyitása olvasásra, ha nem sikerül, akkor hibaüzenet és NULL-t adunk vissza
    FILE *keszlet_fajl = fopen(fajlnev, "r");
    if (keszlet_fajl == NULL)
    {
        printf("\nERROR: Nem létezik \"%s\" nevű fájl a mappában!", fajlnev);
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
                    printf("\nERROR: Nem várt formátum a %s fájl %d. sorában: %s", fajlnev, *n + 1, sor);
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
//Bemenetnek a készletet és a dobozban lévő alkatrészeket kapja meg, valamint a dobozban lévő alkatrészek számát
//Visszatérési értéke 1, ha a készlet kirakható, 0, ha nem
int kirakhato_e(keszlet_t *keszlet, alkatresz_t *doboz, unsigned doboz_n)
{
    //Végigmegyünk az összes alkatrészen a készletben
    for (alkatresz_t *jelenlegi_alkatresz = keszlet->alkatreszek; jelenlegi_alkatresz != NULL; jelenlegi_alkatresz = jelenlegi_alkatresz->next)
    {
        int eleg_ez_a_darab = 0;
        //Végigmegyünk az összes alkatrészen a dobozban
        for (alkatresz_t *doboz_alkatresz = doboz; doboz_alkatresz != NULL; doboz_alkatresz = doboz_alkatresz->next)
        {
            //printf("DEBUG: Comparing part %s, needed: %u with part %s, available: %u\n", jelenlegi_alkatresz->id, jelenlegi_alkatresz->darab, doboz_alkatresz->id, doboz_alkatresz->darab);
            //Ha megtaláljuk az alkatrészt a dobozban, akkor megnézzük, hogy elég van-e belőle
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

//Ez a függvény megkeresi a legdrágább készletet, amely kirakható a dobozban lévő alkatrészekből
//Bemenetnek a készletek tömbjét, a készletek számát, a dobozban lévő alkatrészeket és a dobozban lévő alkatrészek számát kapja meg
//Visszatérési értéke a legdrágább készletre mutató pointer, ha van ilyen, egyébként NULL
keszlet_t* legdragabb_kirakhato_keszlet(keszlet_t *keszletek, unsigned keszletek_n, alkatresz_t *doboz, unsigned doboz_n)
{
    keszlet_t *legdragabb = NULL;
    int max = 0;
    //Végigmegyünk az összes készleten és megnézzük, hogy kirakható-e a dobozban lévő alkatrészekből
    //Ha kirakható és az ára nagyobb, mint a jelenlegi maximum, akkor frissítjük a maximumot és a legdrágább készlet pointerét
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


//A főprogram
//Bekéri a doboz és a készletek fájl nevét, majd beolvassa őket
//Ezutan meghívja a legdrágább kirakható készletet kereső függvényt és kiírja az eredményt
int main(void)
{
    //A változók inicializálása
    unsigned doboz_elemszam;
    unsigned keszlet_elemszam;
    char doboz_fajlnev[100];
    char keszlet_fajlnev[100];

    //Bekérjük a fájlneveket
    printf("Add meg a doboz fájl nevét (pl. doboz.txt): ");
    scanf("%s", doboz_fajlnev);
    printf("Add meg a készletek fájl nevét (pl. keszletek.txt): ");
    scanf("%s", keszlet_fajlnev);

    //Beolvassuk a fájlokat
    alkatresz_t *doboz_alkatreszek = doboz_beolvas(doboz_fajlnev, &doboz_elemszam);
    if (doboz_alkatreszek == NULL) 
        return 1;

    keszlet_t *keszletek = keszlet_beolvas(keszlet_fajlnev, &keszlet_elemszam);
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

    //Megkeressük a legdrágább kirakható készletet
    keszlet_t *legdragabb_keszlet = legdragabb_kirakhato_keszlet(keszletek, keszlet_elemszam, doboz_alkatreszek, doboz_elemszam);
    if (legdragabb_keszlet != NULL)
        printf("\nA legdrágább kirakható készlet: %s (ára: %dFt)", legdragabb_keszlet->nev, legdragabb_keszlet->ar);
    else
        printf("\nEgyik készlet sem rakható ki a dobozban lévő alkatrészekkel");
    free(doboz_alkatreszek);
    free(keszletek);
    return 0;
}