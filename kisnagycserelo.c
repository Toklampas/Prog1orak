#include <stdio.h>

int main()
{
    char a;
    while(scanf("%c", &a) == 1);
    {
        if ('a'>=97 && 'a'<=122)
        {
            a = 'a'-32;
            printf("%c", a);
        }     
        else if ('a'>=65 && 'a'<=90)
        {
            a = 'a'+32;
            printf("%c", a);
        } 
        else
            printf("%c", a);
    }
    return 0;
}