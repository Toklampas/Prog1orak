typedef struct {
    double x;
    double y;
} point;

typedef struct{
    int hour;
    int minute;
    int second;
} time;

typedef struct{
    point position;
    time interval;
} record;

int in_seconds(time t)
{
    return t.second+t.minute*60+t.hour*60*60;    
}

#include <math.h>

double distance(point a, point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y*b.y)*(a.y*b.y));
}

double average_speed(record records[], int n)
{
    double sum_dist = 0, sum_time = 0;
    for(int i = 0; i < n-1; i++)
    {    
        sum_dist += distance(records[i].position, records[i+1].position);
        sum_time += in_seconds(records[i+1].interval);
    }
    return sum_dist/sum_time;
}

-----
Test case #1
time t = {0, 0, 1};
in_seconds(t);
-----
OK

-----
Test case #2
time t = {0, 1, 2};
in_seconds(t);
-----
OK

-----
Test case #3
time t = {1, 2, 3};
in_seconds(t);
-----
OK

-----
Test case #4
time t = {57, 0, 0};
in_seconds(t);
-----
OK

-----
Test case #5
point p = {0.000000, 0.000000};
point q = {3.500000, 0.000000};
distance(p, q);
-----
OK

-----
Test case #6
point p = {3.000000, 0.000000};
point q = {0.000000, -4.000000};
distance(p, q);
-----
Your return value: 3.000000
Correct return value: 5.000000

-----
Test case #7
point p = {-2.800000, 3.140000};
point q = {5.200000, 0.140000};
distance(p, q);
-----
Your return value: 8.012069
Correct return value: 8.544004

-----
Test case #8
point p = {5.968801, 8.232947};
point q = {-6.048973, -3.295545};
distance(p, q);
-----
Your return value: 29.674481
Correct return value: 16.653318

-----
Test case #9
record t[2] = {{{0, 0}, {0, 0, 0}}, {{1, 0}, {0, 0, 1}}};
average_speed(t, 2);
-----
OK

-----
Test case #10
record t[3] = {{{42, 455.5}, {20, 1, 0}}, {{272, -48.5}, {0, 4, 37}}, {{272, 3275.5}, {0, 13, 51}}};
average_speed(t, 3);
-----
Your return value: 163.316514
Correct return value: 3.500000

-----
Test case #11
Random test with 10 records.
-----
Your return value: 249.144504
Correct return value: 1.815181

At least one of the tests failed.