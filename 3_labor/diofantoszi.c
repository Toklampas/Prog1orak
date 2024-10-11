#include <stdio.h>

int main()
{
    int a, b, c, x, y;
    scanf("%d%d%d", &a, &b, &c);
    for(x = 1; a*x<c; x++)
    {
        if((c-a*x)%b == 0) //egesz lesz-e y?
        {
            y = (c-a*x)/b;
            printf("%d %d\n", x, y);
        }
    }
    return 0;
}