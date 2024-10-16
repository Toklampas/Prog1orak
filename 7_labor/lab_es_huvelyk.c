struct imperial
{
    int foot; int inch;
};

typedef struct imperial imperial;

double imperial_to_metric(imperial i)
{
    return i.foot*0.3048+i.inch*(0.3048/12);
}

imperial plus(imperial a, imperial b)
{
    int foot_sum=0, inch_sum=0;
    foot_sum = a.foot+b.foot;
    inch_sum = a.inch+b.inch;
    while (inch_sum >= 12)
    {
        inch_sum -= 12;
        foot_sum++;
    }
    a.foot = foot_sum;
    a.inch = inch_sum;
    return a;
}

#include <stdio.h>

int main()
{
    int foot, inch;
    imperial i;
    while (scanf("%d%d", &foot, &inch) == 2)
    {
        i.foot = foot;
        i.inch = inch;
        printf("%.4lf ", imperial_to_metric(i));
    }
    return 0;
}
