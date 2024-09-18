#include <stdio.h>

int main()
{
    int a;
    int b=1;
    int negyzetsz=0;
    scanf("%d", &a);
    while(b*b <= a)
    {
        if(b*b == a)
            negyzetsz=1;
        b++;
    }

    if(negyzetsz == 1)
        printf("Negyzetszam");
    else
        printf("Nem negyzetszam");
    return 0;
}