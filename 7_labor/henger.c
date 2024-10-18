struct henger
{
    double radius;
    double height;
};

typedef struct henger cylinder;

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

cylinder read_cylinder(void)
{
    cylinder c;
    scanf("%lf%lf", &c.radius, &c.height);
    return c;
}

double cylinder_volume(cylinder c)
{
    return c.radius*c.radius*M_PI*c.height;
}

int main()
{
    cylinder tomb[10];
    for (int i=0; i < 10; i++)
        tomb[i] = read_cylinder();
    for (int i=9; i>=0; i--)
        printf("%.2lf ", cylinder_volume(tomb[i]));
    return 0;
}