typedef struct {
    double x, y;
} point;

#include <math.h>

double distance(point a)
{
    double dist = sqrt(a.x*a.x+a.y*a.y);
    return dist;
}

void sort_points(point t[], int n)
{
    int min, i, j;
    for (i=0; i<n ; ++i)
    {
        min = i;
        for (j = i+1; j<n; ++j)
            if (distance(t[j]) < distance(t[min]))
                min = j;
        point a = t[i];
        t[i] = t[min];
        t[min] = a;
    }
}

int main ()
{
    point t[10] = {{14.7, 9.9}, {-0.4, 1.1}, {9.2, -3.6}, {1.0, 0.6}, {-4.7, -4.1}, {13.2, 0.8}, {-2.2, 0.8}, {3.4, -1.1}, {1.1, 9.4}, {2.6, 8.5}};
    sort_points (t, 10);
    return 0;
}
