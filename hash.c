#include <stdio.h>

int main()
{
    int a, i=1;
    scanf("%d", &a);
    while(i <= a && i <= 100)
        {
        printf("#");
        i++;
        }
    printf("  %d", i - 1);
    return 0;
}