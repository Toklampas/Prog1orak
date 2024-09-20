#include <stdio.h>

int main()
{
    int m, n, i=1;
    scanf("%d%d", &m, &n);
    while(m > 0)
    {
        while(i*m-n < 0)
            i = i+1;
        printf("%d ", i);
        m = i*m-n;
        n = i*n;
    }
    return 0;
}