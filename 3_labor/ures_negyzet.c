#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        printf("x");
    for (int i = 0; i < n-2; i++)
    {
        printf("\nx");
        for (int i = 0; i < n-2; i++)
            printf(".");
        printf("x");
    }
    if(n != 1)
        printf("\n");
    for (int i = 0; i < n && n != 1; i++)
        printf("x");
    return 0;
}
