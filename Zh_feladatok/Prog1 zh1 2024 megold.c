2024 - programozás alapjai 1 - első nagy zárthelyi (hivatalos megoldásokkal)

a) - Mit ír ki az alábbi kódrészlet? printf(”%c”, ’7’ + (8 > 3));
8

b) - Mi lesz a scanf(”%d%d%d”, &a, &b, &c); függvényhívás visszatérési értéke, ha a program standard inputja
0.2 2 2
1 (csak a 0-t olvassa be a-ba, ezért 1 értéket tudott beolvasni a 3-ból)

c) - definiálj felsorolt típust öntetek tárolására (kecsap, mustár, majonéz). Hozz létre egy majonéz értékű változót.
enum ontet {kecsap, mustar, majonez}; enum ontet a  = majonez;

d) - Írj függvényt, mely visszaadja, hogy az első egész paraméterét maradék nélkül osztja-e a második.
int f(int a, int b) { return a % b == 0; }

e) - Hozz létre egy 100 elemű egész tömböt, inicializáld egy egyessel, a maradék legyen nulla.
int t[100] = {1};

f) - Mi lesz b értéke?
double b = 2/4;
b értéke 0.0 lesz, mivel 2/4=0.


----------------------------------------
Ha egy versenyhangyát leteszünk a milliméterpapír origójába, az 10 mm/s sebességű egyenes vonalú egyenletes mozgást kezd végezni.
Ha rákiáltunk, hogy „jobbra!” vagy „stop!”, a hangya azonnal jobbra (−90◦) fordul és folytatja a mozgást, illetve megáll.
Írj programot, mely beolvassa a standard inputról, hogy a hangyára mikor (valós másodperc) mit (J vagy S karakter) kiáltottunk,
és kiírja a standard outputra a hangya (x, y) koordinátáit (milliméterben) a megállást követően. A hangya t = 0 s időpontban az
origóból (0, 0) indul, (0, 1) irányban. A program lehetséges bemenete (az időpontok szigorúan monoton nőnek)
2.0J 3.2J 5.0J 5.9S
Ez esetben az elvárt kimenet
(3, 2)
A hangya pozícióját és aktuális haladási irányát is 2D vektor struktúrában tárold. Írj függvényt, mely a paraméterként
kapott irányt (struktúra) elforgatja jobbra (−90◦-kal), és az új iránnyal tér vissza. Ezt a függvényt használd is a főprogramban!

#include <stdio.h>

typedef struct { double x, y; } vector;

vector right(vector v)
{
    vector s;
    s.x = v.y;
    s.y = -v.x;
    return s;
}

int main()
{
    vector pos = {0.0, 0.0}, vel = {0.0, 10.0};
    double t_prev = 0.0, t;
    char c;
    while (scanf("%lf%c", &t, &c) == 2) {
        double dt = t - t_prev;
        t_prev = t;
        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
        if (c == 'J')
            vel = right(vel);
        else if (c == 'S')
            break;
    }
    printf("(%f,%f)", pos.x, pos.y);
    return 0;
}


----------------------------------------
A Kossuth utcában 1-től 100-ig számozzák a telkeket. A páratlanok a bal, a párosak a jobb oldalon vannak.
A postás reggel végigbiciklizik a Kossuth utca közepén, és amint egy telek sarkával egy vonalba kerül, behajítja a kertbe a napilapot.
Írj programot, mely házszám szerinti sorrendben beolvassa a Kossuth utca telkeinek szélességeit, majd kiírja,
hogy milyen sorrendben hajítja be a postás a napilapot az egyes kertekbe.
A megoldásban vedd figyelembe azt a könnyítést, hogy a postásnak csak 20 napilapja van. Amennyiben egyszerre ér el telekhatárt
a bal és a jobb oldalon, először balra dob, aztán jobbra. A Kossuth utca 1. és a Kossuth utca 2. telkek az utca elejétől 0 m távolságra kezdődnek.
Amennyiben a program bemenete 25 12 20 12 10 20 ..., akkor kimeneten a házszámok elvárt sorrendje 1 2 4 6 3 ....

#include <stdio.h>

int main()
{
    double d[100];
    for (int i = 0; i < 100; i++)
        scanf("%lf", &d[i]);
    int l = 0, r = 1;
    double ldist = 0.0, rdist = 0.0;
    for (int i = 0; i < 20; i++) {
        if (ldist <= rdist) {
            printf("%d ", l + 1);
            ldist += d[l];
            l += 2;
        }
        else {
            printf("%d ", r + 1);
            rdist += d[r];
            r += 2;
        }
    }
    return 0;
}


----------------------------------------
Sajnos a scanf függvénnyel előjel nélküli értékeket csak tízes, nyolcas és tizenhatos számrendszerben tudunk beolvasni.
Írj függvényt, mely tetszőleges, 2 ≤ b ≤ 10 alapú számrendszerben képes előjel nélküli egészek beolvasására.
A függvény kapja meg paraméterként a számrendszer b alapját. A függvény egyesével dolgozza fel a bemeneten érkező karaktereket.
Ha nem megfelelő számjegy karaktert olvasott, azt tegye vissza a standard inputra, és szakítsa meg a beolvasást.
A függvény visszatérési értéke a feldolgozott szám értéke legyen, illetve −1, ha egyetlen számjegyet sem sikerült feldolgoznia.
A beolvasott szám  etszőlegesen hosszú lehet (pl. kezdődhet sokezer nullával), de az érték túlcsordulásával nem kell foglalkoznod.
A c karaktert az ungetc(c, stdin); függvényhívással tudod visszatenni a standard inputra.
Példák:
std input: 102037alma ; b = 3 ; feldolgozott: 1020 ; return: 33 ; inputon marad: 37alma
std input: 102037alma; b = 10 ; feldolgozott: 102037 ; return: 102037 ; inputon marad: alma
std input: 37alma ; b = 3 ; feldolgozott: ; return: −1 ; inputon marad: 37alma

#include <stdio.h>

int scan_base(int b)
{
    int ndigits = 0, value = 0;
    char c;
    while (scanf("%c", &c) == 1) {
        if (c - '0' >= 0 && c - '0' <= b-1) {
            ndigits++;
            value *= b;
            value += c - '0';
        }
        else {
            ungetc(c, stdin);
            break;
        }
    }
    if (ndigits == 0)
        return -1;
    return value;
}