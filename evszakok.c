#include <stdio.h>

enum season {SPRING, SUMMER, AUTUMN, WINTER};

void print_season(enum season s)
{
    switch (s)
    {
    case SPRING: {printf("spring"); return;}
    case SUMMER: {printf("summer"); return;}
    case AUTUMN: {printf("autumn"); return;}
    case WINTER: {printf("winter"); return;}
    }
}

enum season month2season(int n)
{
    if (n>=3 && n<=5) return SPRING;
    else if (n>=6 && n<=8) return SUMMER;
    else if (n>=9 && n<=11) return AUTUMN;
    else if (n==12 || n==1 || n == 2) return WINTER;
    else return 0;
}

int main(void)
{
    int n;
    while (scanf ("%d", &n) == 1)
    {
        print_season(month2season(n));
        printf(" ");
    }
    return 0;
}