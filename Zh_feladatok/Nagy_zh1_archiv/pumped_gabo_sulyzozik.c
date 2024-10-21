typedef enum {FELVESZ, KINYOM, LEENGED, LETESZ} tevekenyseg;

typedef struct
{
    double idopont;
    tevekenyseg tevekenyseg;
} esemeny;

#include <stdio.h>
#include <string.h>

esemeny beolvas()
{
    esemeny esemeny;
    char input_text[7];
    scanf("%lf%s", &esemeny.idopont, input_text);
    if (strcmp(input_text, "felvesz") == 0)
        esemeny.tevekenyseg = FELVESZ;
    else if (strcmp(input_text, "kinyom") == 0)
        esemeny.tevekenyseg = KINYOM;
    else if (strcmp(input_text, "leenged") == 0)
        esemeny.tevekenyseg = LEENGED;
    else if (strcmp(input_text, "letesz") == 0)
        esemeny.tevekenyseg = LETESZ;
    return esemeny;
}

double munkaido(esemeny *naplo, int n)
{
    double sum = 0, start = 0;
    for (int i = 0; i < n; i++)
    {
        if (naplo[i].tevekenyseg == KINYOM)
            start = naplo[i].idopont;
        else if (naplo[i].tevekenyseg == LEENGED)
            sum += naplo[i].idopont - start;
    }
    return sum;
}

int main()
{
    esemeny naplo[10];
    for (int i = 0; i < 10; i++)
        naplo[i] = beolvas();
    printf("%.2lf", munkaido(naplo, 10));
    return 0;
}