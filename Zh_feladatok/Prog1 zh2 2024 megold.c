2024 - programozás alapjai 1 - második nagy zárthelyi (hivatalos megoldásokkal)

* a */
char *firstb(char *str)
{
	for (;*str != '\0'; str++)
		if (*str == 'b')
			return str;
	return NULL;
}

/* b */
double (*p)(double) = sqrt;

/* c */

char miki[62*7+1] = "";
for (int i = 0; i < 62; i++)
	strcat(miki, "mikulas");

/* d */

int b[5];
FILE *f = fopen("binaris.dat", "rb");
fread(b, 5, sizeof(int), f);
fclose(f);

----------------------------------------
Írj programot, mely a standard inputról komplex számokat olvas be kanonikus (valós rész, képzetes rész)
alakban amíg tud, majd a beolvasáshoz képest fordított sorrendben kiírja azok komplex konjugáltjait.
Amennyiben a program bemenete 2.0 3.2 5.0 7.3 4.0 -5.2, akkor kimenete legyen 4.0 5.2 5.0 -7.3 2.0 -3.2.
A bemeneten az egyes számokat szóközök választják el. A megoldáshoz a beolvasott komplex számokból építs
strázsa nélküli, egyszeresen láncolt listát (verem). Minden listaelem egy komplex szám valós és képzetes részét tárolja.
Az elemek komplex konjugáltjait az ebben a veremben lévő adatok alapján írd ki a kimenetre.
Minden elem kiírása után szabadítsd is fel az adott listaelemet. Feltételezheted, hogy a bemenet helyes, és van memória.

#include <stdio.h>
#include <stdlib.h>

typedef struct tria_elem {
	double re, im;
	struct tria_elem *next;
} tria_elem, *tria_ptr;

int main()
{
	double a, b, c;
	tria_ptr head = NULL;
	while (scanf("%lf%lf", &a, &b) == 2)
	{
		tria_ptr p = malloc(sizeof(tria_elem));
		p->re = a; p->im = b;
		p->next = head;
		head = p;
	}

	while (head)
	{
		tria_ptr p = head->next;
		printf("%f %f\n", head->re, -head->im);
		free(head);
		head = p;
	}

	return 0;
}

----------------------------------------
Egy szöveges fájl első egész bejegyzése a fájlban tárolt alkoholos italok darabszámát adja meg.
Az ezt követő sorok egy-egy alkoholos italt adnak meg két valós értékkel: Az ital térfogata (liter), illetve az ital alkoholtartalma (térfogatszázalék).
(a) Hozz létre típust egy ital tárolására.
(b) Írj függvényt, mely paraméterként a fájl nevét kapja, és visszatér a benne tárolt italok dinamikus tömbjével.
(c) Írj főprogramot, mely a függvény segítségével beolvassa az "alkohol.txt" tartalmát egy dinamikus tömbbe, majd kiírja a standard outputra,
hogy ha minden 30%-nál erősebb italt megiszunk, összesen hány liter alkohol jut a szervezetünkbe.
Feltételezheted, hogy a bemenet helyes, és van memória.
A program ne szivárogtasson memóriát.

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	double V, percent;
} alcohol;

alcohol *read(char *fname, int *n)
{
	FILE *f = fopen(fname, "r");
	int m;
	fscanf(f, "%d", &m);
	alcohol *alc = malloc(sizeof(alcohol) * m);
	for (int i = 0; i < m; i++)
		fscanf(f, "%lf%lf", &alc[i].V, &alc[i].percent);
	*n = m;
	fclose(f);
	return alc;
}

int main()
{
	int n;
	alcohol *alc = read("alkohol.txt", &n);
	double sum;
	for (int i = 0; i < n; i++)
		if (alc[i].percent > .3)
			sum += alc[i].V * alc[i].percent;
	printf("%f", sum);
	free(alc);
	return 0;
}

----------------------------------------
Egy bináris fa olyan családot tárol, ahol minden szülőnek legfeljebb két gyermeke van.
Minden elem tárolja a születési évszámát, és két pointert a gyermekeire.
Ha valakinek nincs két gyermeke, akkor a pointerek közül legalább egy NULL-pointer.
(a) Hozd létre a fatípust!
(b) Írj függvényt, mely paraméterként a bináris családfa gyökérpointerét kapja, és visszaadja, hogy a családban hány ikerpár van.
Ikerpárnak az azonos évben született testvéreket tekintjük.
A rekurzív megoldást az alábbiak szerint add meg:
Az üres családban nincsenek ikrek.
Ha a család nem üres, akkor vizsgáld meg, hogy a gyökérelemnek ikrei vannak-e.
Ehhez vedd hozzá a bal és a jobb részfában található ikrek darabszámát.

#include <stddef.h>

typedef struct elem { int birth; struct elem *left, *right; } tree_elem, *tree_ptr;

int ntwins(tree_ptr root)
{
	int n = 0;
	if (root == NULL)
		return 0;
	if (root->left != NULL && root->right != NULL)
		n = root->left->birth == root->right->birth;
	return n + ntwins(root->left) + ntwins(root->right);
}