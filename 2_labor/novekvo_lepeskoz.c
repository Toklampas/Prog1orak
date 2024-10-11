#include <stdio.h>

int main()
{
    int a, b, c=1;
    scanf("%d%d", &a, &b);
    while(a <= b)
    {
        printf("%d ", a);
        a = a+c;
        c++;
    }
    return 0;
}