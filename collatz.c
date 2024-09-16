#include <stdio.h>

int main()
{
    int a, i = 0;
    scanf("%d", &a);
    while (a != 1)
    {
        if((a % 2) == 0) //ha paros
            a = a/2;
        else //ha paratlan
            a = 3*a+1;
        i++;
    }
    printf("%d", i);
    return 1;
}