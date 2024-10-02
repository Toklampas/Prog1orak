#include <stdio.h>

int main()
{
    char a;
    while(scanf("%c", &a) == 1)
    {
        if (a>=97 && a<=122)
            printf("%c", a-32);   
        else if (a>=65 && a<=90)
            printf("%c", a+32);
        else
            printf("%c", a);
    }
    return 0;
}
