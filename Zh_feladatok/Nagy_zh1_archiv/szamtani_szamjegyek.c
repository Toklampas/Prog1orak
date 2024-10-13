#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    for (int i = a; i < b; i++)
        for (int d = 0; d <= 4; d++)
            if ((i%10)+d == (i/10)%10 && ((i/10)%10)+d == (i/100)%10)
                printf("%d ", i);
            else if ((i%10)-d == (i/10)%10 && ((i/10)%10)-d == (i/100)%10)
                printf("%d ", i);
    return 0;
}