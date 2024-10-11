#include <stdio.h>

int main()
{
    double load = 0.0, in=0.0;
    while (scanf("%lf", &in) == 1)
    {
        if (load+in > 2.0)
        {
            printf("%.3f ", 2-load);
            load = 0;
            load += in;
        }
        else
            load += in;
    }
    if (load != 0.0)
        printf("%.3f", 2-load);
    return 0;
}