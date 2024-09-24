#include <stdio.h>

int main()
{
    int a, max=0, min=0;
    while (scanf("%d", &a) == 1)
        if (a < 0 && (a > min || min == 0))
            min = a;
        else if (a > 0 && (a < max || max == 0))
            max = a;
    if (min == 0 && max == 0)
        printf("--- ---");
    else if (min == 0)
        printf("--- %d", max);
    else if (max == 0)
        printf("%d ---", min);
    else
        printf("%d %d", min, max);
    return 0;
}