#include <stdio.h>
#include <limits.h>

int main ()
{
    unsigned long long int sor[100]={0}, input;
    int loc=2;
    for (int i = 0; i < 2; i++)
        {
            scanf("%llu", &input);
            sor[i] = input;
        }
    while (sor[loc-1] <= ULLONG_MAX - sor[loc-2])
    {
        sor[loc] = sor[loc-1] + sor [loc-2];
        loc++;
    }
    printf("%d", loc-1);
    return 0;
}
