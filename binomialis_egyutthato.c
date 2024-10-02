#include <stdio.h>

int main()
{
    unsigned long long n, k, lnko, eredmeny=1;
    int num[40]={0}, den[40]={0};
    scanf("%llu%llu", &n, &k);
    if (k > n-k)
        k = n-k;
    for (int i = 0; i < k; i++)
    {
        num[i] = n-i;
        den[i] = k-i;
    }
    for (int i = 0; i < k; i++) 
    {
        for (int j = 0; j < k; j++) 
        {
            int a = num[i];
            int b = den[j];
            while(b > 0)
            {
                int c = b;
                b = a%b;
                a = c;
            }
            if (a > 1)
            {
                num[i] /= a;
                den[j] /= a;
            }
        }
    }
    for (int i = 0; i < k; i++)
        eredmeny *= num[i];
    printf("%llu", eredmeny);
    return 0;
}

//32153 32150