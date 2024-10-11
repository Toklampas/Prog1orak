#include <stdio.h>

int gcd(int a, int b)
{
   while(b > 0)
    {
        int c = b;
        b = a%b;
        a = c;
    }
    return a; 
}

int relative_primes(int a, int b)
{
    if (gcd(a, b) == 1)
        return 1;
    else return 0;
}

int main()
{
    int a, b, count=0;
    while (scanf("%d%d", &a, &b) == 2)
        count += relative_primes(a, b);
    printf("%d", count);
    return 0;
}