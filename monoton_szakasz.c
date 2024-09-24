#include <stdio.h>

int main()
{
    int a, prev, novekvo = 2;
    if(scanf("%d", &a) == 1)
        {
            prev = a;
            printf("%d", a);
        }
    while (scanf("%d", &a) == 1)
        {
            if (prev < a && novekvo == 2)
                novekvo = 1;
            else if (prev > a && novekvo == 2)
                novekvo = 0;
            if (novekvo == 1 && a > prev)
                printf(" %d", a);
            else if (novekvo == 0 && a < prev)
                printf(" %d", a);
            else break;
            prev = a;
        }
    return 0;
}