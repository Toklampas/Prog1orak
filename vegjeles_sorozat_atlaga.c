#include <stdio.h>

int main()
{
    int sum=0, n=0, a;
    scanf("%d", &a);
    while(a != 0)
    {
        sum = sum + a;
        n++;
        scanf("%d", &a);
    }
    printf("%.2f", (double)sum/n);
    return 0;
}