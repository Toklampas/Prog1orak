#include <stdio.h>

int interval(int start, int length)
{
    int n = 0;
    for (int i = start; i < start + length; i++)
        if ((i/10)%10 < i%10)
            n++;
    return n;
}

int main()
{
    int start, length, min = -1;
    while (scanf("%d%d", &start, &length) == 2)
        if (interval(start, length) < min || min == -1)
            min = interval(start, length);
    printf("%d", min);
    return 0;
}