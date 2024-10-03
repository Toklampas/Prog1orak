#include <float.h>
#include <math.h>
#include <stdio.h>

int main ()
{
    double x, a;
    int n=0;
    scanf("%lf%lf", &a, &x);
    printf("%d %.16E\n", n, x);
    while (fabs((x*x)-a)/a > 10*DBL_EPSILON)
    {
        x = (x/2)+(a/(2*x));
        n++;
        printf("%d %.16E\n", n, x);
    }
    return 0;
}