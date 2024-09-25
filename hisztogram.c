#include <stdio.h>

int main()
{
    int a;
    int j[5]={0};
    while (scanf("%d", &a) == 1)
        j[a-1] += 1;
    for (int i = 5; i > 0; i--)
        printf("%d: %d db\n", i, j[i-1]);
    return 0;
}       