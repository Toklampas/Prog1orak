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
    int input[10], n, out=0;
    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &n);
        input[i] = n;
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            out += relative_primes(input[i], input[j]);
        }
    }
    printf("%d", out/2);
    return 0;
}