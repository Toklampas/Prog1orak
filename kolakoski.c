#include <stdio.h>

int main()
{
    int sor[100]={1};
    int n, o=1;
    scanf("%d", &n);
    for (int i = 0; i < 100; i++)
        {
            sor[i] = i+1;
            o++;
        }
}