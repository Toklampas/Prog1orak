#include <stdio.h>

int main()
{
    double u[10]={0};
    int n=0;
    double a, sum=0.0;
    while (scanf("%lf", &a)==1)
        {
            if (n < 10)
                {
                    u[n] = a;
                    n++;
                }
            else 
                {
                    for (int i = 0; i < 10; i++)
                        u[i] = u[i+1];
                    u[9] = a;
                }
        }
    for (int i = 0; i < 10; i++)
        {
            sum = sum + u[i];
        }
    printf("%.3f", sum/n);
    return 0;
}