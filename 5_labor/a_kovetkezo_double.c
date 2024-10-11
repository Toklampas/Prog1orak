#include <stdio.h>

int main()
{
    double a, d, utolso_d;
    scanf("%lf", &a);
    d = a;
    if (a == 0.0)
        return 0;
    while (a+d > a)
    {
        utolso_d = d;
        d /= 2.0;
    }  
    printf("%.5E", (a+utolso_d)-a);
    return 0;
}