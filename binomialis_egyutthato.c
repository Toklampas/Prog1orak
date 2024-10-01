#include <stdio.h>

int main()
{
    unsigned long long n, k, lnko, eredmeny;
    int num[40]={0}, den[40]={0};
    scanf("%llu%llu", &n, &k);
    for (int i = 0; i < n-(n-k); i++)
    {
        num[i] = n-i;
        den[i] = (n-(n-k))-i;
    }
    for (int i = 0; i < k; i++) 
    {
        for (int j = 0; j < k; j++) 
        {
            while(den[j] > 0)
            {
                int c = den[j];
                den[j] = num[i]%den[j];
                num[i] = c;
            }
            if (lnko > 1)
            {
                num[i] /= lnko;
                den[j] /= lnko;
            }
        }
    }
    for (int i = 0; i < k; i++)
        eredmeny *= num[i];
    printf("%llu", eredmeny);
    return 0;
}