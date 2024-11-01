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
    unsigned carry = 0;
    for (int i = 0; i < out.length-1; i++)
    {
        //megkeressuk hogy melyik ket bajtot kell osszeadni lepesenkent,
        //ha valamelyik szam rovidebb, ahelyett 0-t veszunk
        unsigned byteA = 0, byteB = 0, sum = 0;
        if (i < a.length)
            byteA = a.number[i];
        if (i < b.length)
            byteB = b.number[i];
        //ket bajt osszead, plusz az atvitel ha van
        sum = byteA + byteB + carry;
        //mennyi marad kimenetnek, ha levonjuk azt amit majd atviszunk
        out.number[i] = sum % 256;
        //mennyi lesz at atvitel erteke (hanyszor eri el a 256ot)
        carry = sum / 256;
    }
    //ha volt atvitel, berakjuk a szam vegere
    out.number[out.length-1] = carry;
    //ha nem volt atvitel, csokkenthetjuk 1-el a kimenet hosszat
    if (carry == 0)
    {
        out.length -= 1;
        out.number = realloc(out.number, out.length);
    }
    return out;
}

int main()
{
    big_number_t a = create("1");
    big_number_t b = create("1");
    big_number_t c = add(a, b);
    char* result = tostring(c);
    printf("%s\n", result);
    return 0;
}