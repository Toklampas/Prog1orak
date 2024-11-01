#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned length;
    unsigned char* number;
} big_number_t;

big_number_t create(char* s)
{
    big_number_t out;
    //el kell osztani 2-vel, mert 2 szam kerul egy bajtba (+1 hogy a paratlan is jol legyen kezelve)
    out.length = (strlen(s) + 1) / 2;
    out.number = (unsigned char*)calloc(out.length, sizeof(unsigned char));
    for (int i = 0; i < out.length; i++)
        //tomb feltoltese visszafele, %2x: ket karakter hexadecimalis unsignedban
        sscanf(&s[2 * (out.length - 1 - i)], "%2x", &out.number[i]);
    return out;
}

char *tostring(big_number_t a)
{
    //minden bajt ket karakter, plusz 1 a lezaro 0 miatt
    char* str = (char*)calloc(a.length * 2 + 1, sizeof(char));
    for (int i = 0; i < a.length; i++)
    {
        //str-ben kettesevel haladunk, inputon forditott sorrendben megyunk vegig
        sprintf(&str[i * 2], "%2x", a.number[a.length - 1 - i]);
        //ha a szam csak egy karaktert foglal, a masik karakter legyen nulla
        if (str[i*2] == ' ')
            str[i*2] = '0'; 
    }
    return str;
}

void destroy(big_number_t *a)
{
    free((*a).number);
    (*a).length = 0;
    (*a).number = NULL;
}

big_number_t add (big_number_t a, big_number_t b)
{
    big_number_t out;
    //annyi lesz a kimenet hossza amennyi a hosszabb input, plusz 1 ha tortenik atvitel
    if (a.length > b.length)
        out.length = a.length + 1;
    else
        out.length = b.length + 1;
    out.number = (unsigned char*)calloc(out.length, sizeof(unsigned char));
    for (int i = 0; i < out.length; i++)
    {
    }
    return out;
}

int main()
{
    big_number_t a = create("ff01");
    char* sumStr = tostring(a);
    destroy(&a);
    free (sumStr);
    return 0;
}