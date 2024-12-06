#include <stdio.h>

int a(int drawn[])
{
    int sum = 0;
    for (int i = 0; i < 10; i++)
        if (drawn[i] == 1)
            sum += i;
    return sum;
}

void b(int drawn[], int *remaining, int *dangerous)
{
    *remaining = 0;
    *dangerous = 0;
    int sum = a(drawn);
    for (int i = 0; i < 10; i++)
        if (drawn[i] == 0)
        {
            (*remaining)++;
            if (sum + i > 21)
                (*dangerous)++;
        }
}

int main()
{
    int drawn[10] = {0};
    int n;
    int sum = 0;
    while (1)
    {
        int remaining, dangerous;
        b(drawn, &remaining, &dangerous);
        if (dangerous > remaining / 2)
            break;
        if (scanf("%d", &n) != 1)
            break;
        drawn[n] = 1;
        sum = a(drawn);
        if (sum > 21)
        {
            printf("LOSE\n");
            return 0;
        }
    }
    printf("WIN\n");
    return 0;
}