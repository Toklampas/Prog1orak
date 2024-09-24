#include <stdio.h>

int main()
{
    int p[100]={0};
    int a, n=0;
    while (scanf("%d", &a) == 1 && a != 0)
        if (a > 0)
            {
            p[n] = a;
            n++;
            }
    for (int i=0; i<n; i++)
        printf("%d ", p[n-1-i]);
    return 0;
}