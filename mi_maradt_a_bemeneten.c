#include <stdio.h>

int main()
{
    double a, sum=0.000;
    char c;
    while (scanf("%lf", &a) == 1)
        {
            sum = sum+a;
        }
    printf("%.3f\n", sum);
    while (scanf("%c", &c) == 1)
        printf("%c", c);
    return 0;
}