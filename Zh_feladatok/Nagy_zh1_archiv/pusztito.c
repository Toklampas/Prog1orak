#include <stdio.h>

int main()
{
    double load = 0.0, in;
    while (scanf("%lf", &in) == 1)
    {
        if (load+in > 2.0)
        {
            printf("%.3f ", 2-load);
            load = 0;
        }
        else
            load += in;
    }
    if (load != 0.0)
        printf("%.3f", load);
    return 0;
}