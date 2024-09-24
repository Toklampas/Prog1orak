#include <stdio.h>

int main()
{
    int a, min, max;
    scanf("%d", &a);
    if(a<0)
        a = -a;
    max = a;
    min = a;
    while(a!=0)
    {
        if(a<0)
            a = -a;
        if(a>max)
            max = a;
        if(a<min)
            min = a;
        scanf("%d", &a);    
    }
    printf("%d", max-min);
    return 0;
}
