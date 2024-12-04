typedef struct {
    double x, y;
} point;

#include <stdlib.h>

int compare(point *a, point *b)
{
    double dist1 = a->x * a->x + a->y * a->y;
    double dist2 = b->x * b->x + b->y * b->y;

    if (dist1 < dist2)
        return -1;
    else if (dist1 > dist2)
        return 1;
    else
        return 0;
}

void sort_points(point *points, int n)
{
    qsort(points, n, sizeof(point), compare);
}